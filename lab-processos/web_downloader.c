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

void process_url_name(char *str){
	size_t len = strlen(str);
	char resposta[1024] = "";
	int found_1 = 0;
	int found_c = 0;
	int idx_dot;

	for (int i = 0; i < len; i++){
		if (strcmp(str[i], ".")){
			idx_dot = i;
		}
	}

    for (int i = 0; i < len; i++){
		if (strcmp(str[i], ":") && !found_1){
			found_1 = 1;
		}

		if (found_1 && strcmp(str[i], "/") && (found_c < 2)){
			found_c++;
		}

		if (found_1 && (found_c >= 2)){
			if (!strcmp(str[i], "/") && !strcmp(str[i], ".")){
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

	str = resposta;
}

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream){
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

int main(int argc, char *argv[]) {
    pid_t parallel;

	if(argc < 2) {
		printf("Modo de uso: %s <URL> -f <lista_download.txt>\n", argv[0]);
		return 1;
	}

    if (strcmp(argv[1], "-f")){
        FILE* fileo = fopen(argv[2], "r");
		int len_arq = 0;
        char line[256];
        char char_a[5][256] = {""};

        while (fgets(line, sizeof(line), fileo)){
            strcpy(char_a[len_arq], line);
            len_arq++;
        }

        for (int i = 0; i < len_arq; i++){
            char site[256];
            FILE *output;
            CURL *curl;
            int result;

            parallel = fork();

            if (parallel){
                int b=0;
                for (b=0; char_a[i][b]!='\0'; b++);
                if ((char_a[i][b-1] = '\n')) {
                    char_a[i][b-1] = '\0';
                }

                process_url_name(&site); 
                
                output = fopen(site, "wb");

				curl_global_init(CURL_GLOBAL_DEFAULT);
                curl = curl_easy_init();

                if (curl){
                    curl_easy_setopt(curl, CURLOPT_URL, char_a[i]);
                    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
                    curl_easy_setopt(curl, CURLOPT_WRITEDATA, output);
                    curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1L);

                    result = curl_easy_perform(curl);

                    if (result == CURLE_OK){
                        printf("URL %s baixada com sucesso.\n", char_a[i]);
                        curl_easy_cleanup(curl);
                        fclose(output);
                        return 0;
                    }
					else{
                        printf("Erro: %s\n\n", curl_easy_strerror(result));
                        return 0;
                    }     
                }
				else{
                    return 0;
                }
                  
            } 
            else{
                int wst;
                wait(&wst);
            }
        }
    }
	else{
        char site[50];
        FILE *output;
        CURL *curl;
        int result;

        process_url_name(&site);
       
        output = fopen(site, "wb");

        curl = curl_easy_init();
        curl_easy_setopt(curl, CURLOPT_URL, argv[1]);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, output);
        curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1L);

        result = curl_easy_perform(curl);

        if (result == CURLE_OK){
            printf("URL %s baixada com sucesso.\n", argv[1]);
            fclose(output);
            curl_easy_cleanup(curl);
        }
		else{
            printf("Erro: %s\n", curl_easy_strerror(result));
        }  
    }

    return 0;
}

//BIBLIOGRAFIA
//https://www.apriorit.com/dev-blog/344-libcurl-usage-downloading-protocols
//https://curl.se/libcurl/c/https.html
//https://stackoverflow.com/questions/9206091/going-through-a-text-file-line-by-line-in-c/9206332
//https://curl.se/libcurl/c/libcurl-easy.html
//https://www.techgalery.com/2020/12/step-by-step-using-curl-library-using-c.html
//https://stackoverflow.com/questions/1636333/download-file-using-libcurl-in-c-c