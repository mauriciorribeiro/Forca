/* Program: Forca
   By: Mauricio Ramos Ribeiro / Claudio     
   Date: Oct 05, 2019 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/* contant declarations */
#define NUM_TRIES_ALLOWED 3

/* function prototypes */
void clrscrn( void );
void draw_hangman( int incorrect_tries );
char *strdup(const char *src);


int main(void)
{
   /* variable declarations */
   int num_letters       = 0, /* length of word char array */
       count             = 0, /* for word char array       */
       tries             = 0, /* total tries user has used */
       num_vis_chars     = 0, /* # of visible characters   */
       correct_guesses   = 0, /* # of correct guesses      */
       correct_flag      = 0, /* was guess correct?        */
       repeat_flag       = 0, /* was guess a repeat?       */
       rnd               = 0;

   char guess;

   /* array declarations */
   char word[255]              = " ";
   char incorrect_letters[255] = " ";
    
   
   //File
   int i = 0;
   int numPalavras = 0;
   char* palavras[50];
   char line[50];

   FILE *arquivo;
   arquivo = fopen("palavras.txt", "r");

   if (arquivo == NULL)
       return EXIT_FAILURE;

   while(fgets(line, sizeof line, arquivo) != NULL)
   {
       //Adiciona cada palavra no vetor
       palavras[i] = strdup(line);

       i++;

       //Conta a quantidade de palavras
       numPalavras++;
   }

   fclose(arquivo);
    
   //Random
   time_t t;
    
   /* Intializes random number generator */
   srand((unsigned) time(&t));
    
   rnd = rand() % numPalavras;   
       
   strcpy(word,palavras[rnd]);       
           

   num_letters = strlen( word ) - 1;
   char visible_word[num_letters]; /* displays correct guesses */

   /* initialize visble_word */
   for( count = 0; count < num_letters; count++ )
      visible_word[count] = '-';

   visible_word[num_letters] = '\0';

   clrscrn();
   puts( "\nForca" );
   draw_hangman( tries );

   while( tries < NUM_TRIES_ALLOWED )
   {
      printf( "Palavra: %s\n", visible_word );
      printf( "Letras erradas: %s\n", incorrect_letters );
      printf( "\nTente uma letra (e pressione 'Enter'): " );
      scanf( " %c", &guess );

      /* match guess against previous guesses */
      for( count = 0; count < num_letters; count++ )
         if( guess == visible_word[count] || guess == incorrect_letters[count] )
         {
            repeat_flag  = 1;
            correct_flag = 1;
            break;
         }

      if( repeat_flag == 0 )
         /* check for matches in string */
         for( count = 0; count < num_letters; count++ )
         {
            if( guess == word[count] )
            {
               visible_word[count] = guess;
               correct_guesses++;

               if( correct_guesses == num_letters )
               {
                  puts( "\n\nPARABENS! Voce acertou a palavra!" );
                  printf( "Palavra: %s\n\n", visible_word );
                  return 0;
               }

               correct_flag = 1;
            }
         }

      if( correct_flag == 0 )
      {
         incorrect_letters[tries] = guess;
         tries++;
      }

      /* reset flags */
      repeat_flag  = 0;
      correct_flag = 0;

      clrscrn();
      puts( "\nForca" );
      draw_hangman( tries );
   }

   puts( "Voce nao acertou a palavra." );
   printf( "Palavra: %s\n\n", word );

   return 0;
}

/* clrscrn() clears the screen */
void clrscrn( void )
{
   int x = 0;

   for( x = 0; x < 20; x++ )
      printf( "\n" );
}

/* draw_hangman() displays the hangman */
void draw_hangman( int incorrect_tries )
{
/*
 ___
 |  &
 |  O
 | /|\
 | / \
 |
---
*/

   switch( incorrect_tries )
   {
      default:
      {
         puts( "\n  ___" );
         puts( " |" );
         puts( " |" );
         puts( " |" );
         puts( " |" );
         puts( " |" );
         puts( "---" );
         break;
      }

      case 1:
      {
         puts( "\n  ___" );
         puts( " |  &" );
         puts( " |  O" );
         puts( " |" );
         puts( " |" );
         puts( " |" );
         puts( "---" );
         break;
      }

      case 2:
      {
         puts( "\n  ___" );
         puts( " |  &" );
         puts( " |  O" );
         puts( " | /|\\" );
         puts( " |" );
         puts( " |" );
         puts( "---" );
         break;
      }

      case 3:
      {
         puts( "\n  ___" );
         puts( " |  &" );
         puts( " |  O" );
         puts( " | /|\\" );
         puts( " | / \\" );
         puts( " |" );
         puts( "---" );
         break;
      }
   }
}

char *strdup(const char *src) {
    char *dst = malloc(strlen (src) + 1);  // Space for length plus nul
    if (dst == NULL) return NULL;          // No memory
    strcpy(dst, src);                      // Copy the characters
    return dst;                            // Return the new string
}
	