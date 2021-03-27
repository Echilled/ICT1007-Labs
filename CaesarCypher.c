#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CIPHER_KEY 3
int main() { 
  char fileName[20], ch; FILE *fpTxtOriginal, *fpTxtEncrypt, *fpBinDecrypt;     
  FILE *fpBin, *fpBinData; 
  char strTemp[100] = "", strOriginal[100] = "";  
  char strEncrypted[100] = "", strDecrypted[100] = "";  
  char charPlain, charCipher; float floatBin = 0.0; 
  unsigned char dataBin[300] = {0x00}; 
  char strBin[100] ="";
  int i, length, ret;



  printf("\nEnter the name of file to encrypt: ");     
  scanf("%s", fileName); 
 

  printf("Opening original file %s in text mode\n", fileName);     
  fpTxtOriginal = fopen(fileName, "r"); // text mode
  if(fpTxtOriginal == NULL) {         
    printf("File does not exist or error in opening the file %s\n",fileName);         
  exit(1);
  }

  printf("Opening file %s in text mode to write encrypted content\n",  "Lab5_EncryptedText.txt");
  fpTxtEncrypt = fopen("Lab5_EncryptedText.txt", "ab+"); //text mode
  if(fpTxtEncrypt == NULL) {         
    printf("Error in creating %s\n", "Lab5_EncryptedText.txt");        
     fclose(fpTxtOriginal);         
     exit(2);     
     }

    while(1) {         
      ch = fgetc(fpTxtOriginal); 
      if(ch == EOF) { 
        break; 
      }
      else{
        //Perform encryption
      
         if(ch >= 'a' && ch <= 'z'){
			      ch = ch + CIPHER_KEY;
			
			   if(ch > 'z'){
				    ch = ch - 'z' + 'a' - 1;
			    }
        
        }
        else if(ch >= 'A' && ch <= 'Z'){
          	ch = ch + CIPHER_KEY;
			
			      if(ch > 'Z'){
				      ch = ch - 'Z' + 'A' - 1;
			      }
        }

        fputc(ch, fpTxtEncrypt);
      
      
    }
    }
     ret = fseek(fpTxtOriginal, 0, SEEK_SET);
     while(fgets(strTemp, sizeof(strTemp), fpTxtOriginal)) { 
       strcat(strOriginal, strTemp);
     }
     printf("\nOriginal content: %s\n", strOriginal);     
     printf("Encrypted content written into text mode file %s\n", "Lab5_EncryptedText.txt");
     printf("Closing original text mode file %s\n", fileName); 
     printf("Closing encrypted text mode file %s\n", "Lab5_EncryptedText.txt");
     fclose(fpTxtOriginal);
     fclose(fpTxtEncrypt);
     printf("Opening encrypted text mode file %s\n", "Lab5_EncryptedText.txt"); 
     fpTxtEncrypt = fopen("Lab5_EncryptedText.txt", "r"); // text mod

    if(fpTxtEncrypt == NULL) {         
      printf(" File does not exist or error in opening %s\n", "Lab5_EncryptedText.txt");         
      fclose(fpTxtOriginal);         
      exit(4);     
      }
      
    printf("\nEncrypted content: "); 
    if(fgets (strEncrypted, 100, fpTxtEncrypt) != NULL ) {       
      puts(strEncrypted); // write content to stdout    
    }
    printf("Closing encrypted text mode file %s\n", "Lab5_EncryptedText.txt");  
    fclose(fpTxtEncrypt);
}
