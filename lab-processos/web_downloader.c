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

char process_url_name(char *str){
	size_t len = strlen(str);
	char resposta[1024] = "";
	int found_1 = 0;
	int found_c = 0;
	int idx_dot;

	for (int i = 0; i < len; i++){
		if (str[i] == "."){
			idx_dot = i;
		}
	}

    for (int i = 0; i < len; i++){
		if (str[i] == ":" && !found_1){
			found_1 = 1;
		}

		if (found_1 && (str[i] == "/") && (found_c < 2)){
			found_c++;
		}

		if (found_1 && (found_c >= 2)){
			if ((str[i] != "/") && (str[i] != ".")){
				strcat(resposta, str[i]);
			}
			else{
				if (i != idx_dot){
					strcat(resposta, "_");
				}
				else{
					strcat(resposta, ".");
				}
			}
		}
	}

	return resposta;
}

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream){
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

int main(int argc, char *argv[]){
	char input_filename[256];
	pid_t parallel;
	int multiple = 0;

	if(argc < 2) {
		printf("Modo de uso: %s <URL> -f <lista_download.txt>\n", argv[0]);
		return 1;
	}

	for (int i = 1; i < (argc - 1); i++){
		if (strcmp("-f", argv[i]) == 0){
			input_filename = argv[i];
			multiple = 1;
		}
	}

	if (multiple){
		FILE* file = fopen(input_filename, "r");
		int len_file = 0;
		char line[256];
        char arr[5][256] = {""};

        while (fgets(line, sizeof(line), file)){
			len_file++;
            strcpy(arr[len_file], line);
        }

		for (int i = 0; i < len_file; i++){
            FILE *output;
            CURL *curl;
            int result;
            parallel = fork();
            if (!parallel){
				int x = 0;
                for (x = 0; arr[i][x] != "\0"; x++);
                if(arr[i][x-1] = "\n"){
                    arr[i][x-1] = "\0";
                }
            
                char url_c[256] = process_url_name(arr[i]);
                
                output = fopen(url_c, "wb");

				curl_global_init(CURL_GLOBAL_DEFAULT);
                curl = curl_easy_init();

                if (curl){
                    curl_easy_setopt(curl, CURLOPT_URL, arr[i]);
                    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
                    curl_easy_setopt(curl, CURLOPT_WRITEDATA, output);
                    curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1L);

                    result = curl_easy_perform(curl);

                    if (result == CURLE_OK){
                        printf("URL %s baixada com sucesso.", url_c);
                        curl_easy_cleanup(curl);
                        fclose(output);
                        exit(0);
                    }

					else{
                        printf("Erro: %s\n", curl_easy_strerror(result));
                        exit(0);
                    }     
                }
				else {
                    exit(0);
                }
                  
            }

            else {
                int wst;
                wait(&wst);
            }
        }
	}
	
	else{
		char url_c[50];
		char arr[5][256] = {""};
        FILE *output;
        CURL *curl;
        int result;

    	url_c = process_url_name(arr[i]);

        output = fopen(url_c, "wb");

        curl = curl_easy_init();
        curl_easy_setopt(curl, CURLOPT_URL, argv[1]);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, output);
        curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1L);

        result = curl_easy_perform(curl);

        if (result == CURLE_OK){
            printf("URL %s baixada com sucesso.", url_c);
            fclose(output);
            curl_easy_cleanup(curl);
        }
		else{
            printf("Erro: %s\n", curl_easy_strerror(result));
        }  
    }

	curl_global_cleanup();
	
	return 0;
}

//BIBLIOGRAFIA
//https://www.apriorit.com/dev-blog/344-libcurl-usage-downloading-protocols
//https://curl.se/libcurl/c/https.html
//https://stackoverflow.com/questions/9206091/going-through-a-text-file-line-by-line-in-c/9206332
//https://curl.se/libcurl/c/libcurl-easy.html
//https://www.techgalery.com/2020/12/step-by-step-using-curl-library-using-c.html
//https://stackoverflow.com/questions/1636333/download-file-using-libcurl-in-c-c