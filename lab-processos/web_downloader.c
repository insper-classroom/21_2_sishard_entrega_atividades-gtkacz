#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream){
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

void slice_str(const char *str, char *buffer, size_t start, size_t end){
    size_t j = 0;
    for(size_t i = start; i <= end; ++i){
        buffer[j++] = str[i];
    }
    buffer[j] = 0;
}

void process_str(char *str, char *buffer){
	int idx_dot = 0;

	slice_str(str, buffer, 7, strlen(str));
	
	for(int i = 0; i < strlen(buffer); i++){
		if (buffer[i] == '.'){
			idx_dot = i;
		}
	}
	
	for(int i = 0; i < strlen(buffer); i++){
		if ((i != idx_dot) && (buffer[i] == '.' || buffer[i] == '/')){
			buffer[i] = '_';
		}
	}
}

int main(int argc, char *argv[]) {
    pid_t parallel_f;

    if(strcmp(argv[1], "-f") == 0){
        FILE* input = fopen(argv[2], "r");
		int len_i = 0;
        char cur_l[512];
        char tot_l[5][512] = {""};

        while(fgets(cur_l, sizeof(cur_l), input)){
            strcpy(tot_l[len_i], cur_l);
            len_i++;
        }

        for (int i = 0; i < len_i; i++){
            char url_c[512];
            int answer;
			FILE *output;
            CURL *curl;

            parallel_f = fork();
			
            if (parallel_f == 0){
                int b=0;
                for (b=0; tot_l[i][b]!='\0'; b++);
                if ((tot_l[i][b-1] = '\n')) {
                    tot_l[i][b-1] = '\0';
                }

                process_str(argv[1], url_c);
                
                output = fopen(url_c, "wb");

				curl_global_init(CURL_GLOBAL_DEFAULT);
                curl = curl_easy_init();

                if(curl){
                    curl_easy_setopt(curl, CURLOPT_URL, tot_l[i]);
                    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
                    curl_easy_setopt(curl, CURLOPT_WRITEDATA, output);
                    curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1L);

                    answer = curl_easy_perform(curl);

                    if (answer == CURLE_OK){
                        printf("URL %s baixada com sucesso.\n", tot_l[i]);
                        curl_easy_cleanup(curl);
                        fclose(output);
                        return 0;
                    }
					else{
                        printf("Erro: %s\n", curl_easy_strerror(answer));
                        return 0;
                    }     
                }
				else{
                    return 0;
                }
                  
            } 
            else{
                int wait_p;
                wait(&wait_p);
            }
        }
    }
	else{
        char url_c[50];
        FILE *output;
        CURL *curl;
        int answer;

        process_str(argv[1], url_c);

        output = fopen(url_c, "wb");

		curl_global_init(CURL_GLOBAL_DEFAULT);
        curl = curl_easy_init();
        curl_easy_setopt(curl, CURLOPT_URL, argv[1]);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, output);
        curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1L);

        answer = curl_easy_perform(curl);

        if (answer == CURLE_OK){
            printf("URL %s baixada com sucesso.\n", argv[1]);
            fclose(output);
            curl_easy_cleanup(curl);
        }
		else{
            printf("Erro: %s\n", curl_easy_strerror(answer));
        }  
    }

    return 0;
}

//BIBLIOGRAFIA
//https://www.apriorit.com/dev-blog/344-libcurl-usage-downloading-protocols
//https://curl.se/libcurl/c/https.html
//https://stackoverflow.com/questions/9206091/going-through-a-text-file-cur_l-by-cur_l-in-c/9206332
//https://curl.se/libcurl/c/libcurl-easy.html
//https://www.techgalery.com/2020/12/step-by-step-using-curl-library-using-c.html
//https://stackoverflow.com/questions/1636333/download-file-using-libcurl-in-c-c
//https://stackoverflow.com/questions/26620388/c-substrings-c-string-slicing