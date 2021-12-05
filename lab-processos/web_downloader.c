#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char process_url_name(char *str){
	size_t len = strlen(str);
    char resposta[1024] = '';
	int found_1 = 0;
	int found_2 = 0;
	int found_3 = 0;

    for (i = 0; i < len; i++){
		if (str[i] == ':' && !found1){
			found_1 = 1;
		}

		if (found1 && !found2 && str[i] == '/'){
			found2 = 1;
		}

		if (found2 && !found3 && str[i] == '/'){
			found3 = 1;
		}

		if (found1 && found2 && found3){
			if ((str[i] != '/') && (str[i] != '.')){
				strcat(resposta, str[i]);
			}
			else{
				strcat(resposta, '_');
			}
		}
	}

	return resposta;
}

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream){
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

void slice(const char * str, char * buffer, size_t start, size_t end){
    size_t j = 0;
    for ( size_t i = start; i <= end; ++i ) {
        buffer[j++] = str[i];
    }
    buffer[j] = 0;
}

int main(int argc, char *argv[]){
	CURL *curl;
	CURLcode res;
	char input_filename[];
	pid_t paralel;
	int multiple = 0;

	if(argc < 2) {
		printf('Modo de uso: %s <URL> -f <lista_download.txt>\n', argv[0]);
		return 1;
	}

	for (i = 1; i < (argc - 1); i++){
		if (strcmp('-f', argv[i]) == 0){
			input_filename = argv[i];
			multiple = 1;
		}
	}

	if (multiple){
		FILE* file = fopen(input_filename, 'r');
		int len_file = 0;
		char line[256];
        char arr[5][256] = {''};
        while (fgets(line, sizeof(line), input)){
			len_file++;
            strcpy(arr[len_file], line);
        }

		for (int i = 0; i < len_file; i++){
            FILE *output;
            CURL *curl;
			char site[256];
            int result;
            paralel = fork();
            if (!paralel){
                for (b = 0; arr[i][b] != '\0'; b++);
                if ((arr[i][b-1] = '\n')) {
                    arr[i][b-1] = '\0';
                }

                if (success){
                    slice(arr[i], site, 8, strlen(arr[i]));
                }
				else {
                    slice(arr[i], site, 7, strlen(arr[i]));
                }
            
                //PROCESSA A STRING FILHO DA PUTA
                
                output = fopen(site, 'wb');

                // Operacoes com Curl
                // Baseado em: https://www.youtube.com/watch?v=PQF_IU2YXIg&ab_channel=HathibelagalProductions
                
                curl = curl_easy_init();

                if (curl){
                
                    curl_easy_setopt(curl, CURLOPT_URL, arr[i]);
                    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
                    curl_easy_setopt(curl, CURLOPT_WRITEDATA, output);
                    curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1L);

                    result = curl_easy_perform(curl);

                    if (result == CURLE_OK){
                        printf('%s baixado com sucesso!\n\n', arr[i]);
                        curl_easy_cleanup(curl);
                        fclose(output);
                        exit(0);
                    } else{
                        printf('Erro: %s\n\n', curl_easy_strerror(result));
                        exit(0);
                    }     
                } else {
                    exit(0);
                }
                  
            } 
            else {
                int wst;
                wait(&wst);
            }
        }
	}
	
	curl_global_init(CURL_GLOBAL_DEFAULT);
 
	curl = curl_easy_init();

	if(curl){
		curl_easy_setopt(curl, CURLOPT_URL, 'http://help.websiteos.com/websiteos/example_of_a_simple_html_page.htm');
 
		res = curl_easy_perform(curl);

		if(res != CURLE_OK)
			fprintf(stderr, 'curl_easy_perform() falhou: %s\n',
							curl_easy_strerror(res));
 
		curl_easy_cleanup(curl);
	}
 
	curl_global_cleanup();

    printf('URL %s baixada com sucesso.', url);
    
	return 0;
}