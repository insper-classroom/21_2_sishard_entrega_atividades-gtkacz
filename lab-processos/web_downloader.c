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
    for (size_t i = start; i <= end; ++i ) {
        buffer[j++] = str[i];
    }
    buffer[j] = 0;
}

void slice_str(const char * str, char * buffer, size_t start, size_t end){
    size_t j = 0;
    for ( size_t i = start; i <= end; ++i ) {
        buffer[j++] = str[i];
    }
    buffer[j] = 0;
}

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream){
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

int main(int argc, char *argv[]) {
    pid_t parallel_f;

    if (strcmp(argv[1], "-f") == 0){
        FILE* input = fopen(argv[2], "r");
		int len_i = 0;
        char line[512];
        char arr[5][512] = {""};

        while (fgets(line, sizeof(line), input)){
            strcpy(arr[len_i], line);
            len_i++;
        }

        for (int i = 0; i < len_i; i++){
            char url_c[512];
            int result;
			FILE *output;
            CURL *curl;

            parallel_f = fork();
			
            if (parallel_f == 0){
				int idx_dot = 0;

                int b=0;
                for (b=0; arr[i][b]!='\0'; b++);
                if ((arr[i][b-1] = '\n')) {
                    arr[i][b-1] = '\0';
                }

                slice_str(arr[i], url_c, 7, strlen(arr[i]));

                for (int x = 0; x < strlen(url_c); x++){
                    if (url_c[x] == '.'){
                        idx_dot = x;
                    }
                    
                }
         
                for (int p = 0; p < strlen(url_c); p++){
                    if ((url_c[p] == '.' || url_c[p] == '/') && (p != idx_dot)){
                        url_c[p] = '_';
                    }
                }   
                
                output = fopen(url_c, "wb");

				curl_global_init(CURL_GLOBAL_DEFAULT);
                curl = curl_easy_init();

                if(curl){
                    curl_easy_setopt(curl, CURLOPT_URL, arr[i]);
                    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
                    curl_easy_setopt(curl, CURLOPT_WRITEDATA, output);
                    curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1L);

                    result = curl_easy_perform(curl);

                    if (result == CURLE_OK){
                        printf("URL %s baixada com sucesso.\n", arr[i]);
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
        char url_c[50];
        FILE *output;
        CURL *curl;
        int result;
		int idx_dot = 0;

        slice_str(argv[1], url_c, 7, strlen(argv[1]));
       
        for (int i = 0; i < strlen(url_c); i++){
            if (url_c[i] == '.'){
                idx_dot = i;
            }
        }
        
        for (int i = 0; i < strlen(url_c); i++){
            if ((url_c[i] == '.' || url_c[i] == '/') && (i != idx_dot)){
                url_c[i] = '_';
            }
        }
       
        output = fopen(url_c, "wb");

		curl_global_init(CURL_GLOBAL_DEFAULT);
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
//https://stackoverflow.com/questions/26620388/c-substrings-c-string-slicing