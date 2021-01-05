#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/time.h>

/* Inserite eventuali extern modules qui */

/* ************************************* */

enum { MAXLINES = 200 };
enum { LIN_LEN = 5 };
enum { LOUT_LEN = 15 };

long long current_timestamp() {
    struct timespec tp;
	clock_gettime(CLOCK_REALTIME, &tp);
	/* te.tv_nsec nanoseconds divide by 1000 to get microseconds*/
	long long nanoseconds = tp.tv_sec*1000LL + tp.tv_nsec; // caculate nanoseconds
    return nanoseconds;
}


int main(int argc, char *argv[]) {
    int i = 0;
    char bufferin[MAXLINES*LIN_LEN+1] ;
    char line[1024];
    long long tic_c, toc_c, tic_asm, toc_asm;

    char bufferout_c[MAXLINES*LOUT_LEN+1] = "" ;
    char bufferout_asm[MAXLINES*LOUT_LEN+1] = "" ;

    FILE *inputFile = fopen(argv[1], "r");

    if(argc != 3)
    {
        fprintf(stderr, "Syntax ./test <input_file> <output_file>\n");
        exit(1);
    }

    if (inputFile == 0)
    {
        fprintf(stderr, "failed to open the input file. Syntax ./test <input_file> <output_file>\n");
        exit(1);
    }

    while (i < MAXLINES && fgets(line, sizeof(line), inputFile))
    {
        i = i + 1;
        strcat( bufferin, line) ;
    }

    bufferin[MAXLINES*LIN_LEN] = '\0' ;

    fclose(inputFile);


    /* ELABORAZIONE in C */
    tic_c = current_timestamp();

    /* è possibile inserire qui il codice per l'elaborazione in C (non richiesto per l'elaborato) */
    /* questo pezzo di codice è solo una base di partenza per fare dei check sui dati */
    /*
    int c = 0;
    while ( bufferin[c] != '\0') {
      printf( "%c", bufferin[c] );
      strncat( bufferout_asm, &bufferin[c], 1);
      c = c + 1 ;
    }
    */

    toc_c = current_timestamp();

  	long long c_time_in_nanos = toc_c - tic_c;

    /* FINE ELABORAZIONE C */


    /* INIZIO ELABORAZIONE ASM */

    tic_asm = current_timestamp();

    /* Assembly inline:
    Inserite qui il vostro blocco di codice assembly inline o richiamo a funzioni assembly.
    Il blocco di codice prende come input 'bufferin' e deve restituire una variabile stringa 'bufferout_asm' che verrà poi salvata su file. */

    __asm__(
      "movl %0, %%esi;"
      "movl %1, %%edi;"

      "xor %%dl, %%dl;"
      "for_1:"              // ciclo for per le prime 3 righe di input
        "cmp %65, %%esi;"
        "je parking_a;"
        "cmp %66, %%esi;"
        "je parking_b;"
        "cmp %67, %%esi;"
        "je parking_c;"
        "addl %4, %%esi;"
        "jmp for_1;"

        "parking_a:"        // se il parcheggio è A
          "addl %12, %%esi;"
          "cmp %58, %%esi;"
          "jl saltoa1;"
          "saltoa2:"
          "subl %4, %%esi;"
          "movl %0, %%ah;"
          "movl %%esi, %%al;"
          "jmp jump;"
          "saltoa1:"
            "cmp %47, %%esi;"
            "jl saltoa2;"
            "subl %4, %%esi;"
            "movl %esi, %%ah;"
            "addl %4, %%esi;"
            "movl %esi, %%al;"
          "jmp jump;"

        "parking_b:"        // se il parcheggio è B
          "addl %12, %%esi;"
          "cmp %58, %%esi;"
          "jl saltob1;"
          "saltob2:"
          "subl %4, %%esi;"
          "movl %0, %%bh;"
          "movl %%esi, %%bl;"
          "jmp jump;"
          "saltob1:"
            "cmp %47, %%esi;"
            "jl saltob2;"
            "subl %4, %%esi;"
            "movl %esi, %%bh;"
            "addl %4, %%esi;"
            "movl %esi, %%bl;"
          "jmp jump;"

        "parking_c:"        // se il parcheggio è C
          "addl %12, %%esi;"
          "cmp %58, %%esi;"
          "jl saltoc1;"
          "saltoc2:"
          "subl %4, %%esi;"
          "movl %0, %%ch;"
          "movl %%esi, %%cl;"
          "jmp jump;"
          "saltoc1:"
            "cmp %47, %%esi;"
            "jl saltoc2;"
            "subl %4, %%esi;"
            "movl %esi, %%ch;"
            "addl %4, %%esi;"
            "movl %esi, %%cl;"
          "jmp jump;"

        "jump:"
        "addl %12, %%esi;"
        "inc %%dl;"
        "cmp %3, %%dl;"
        "jl for_1;"
        // FINE CICLO FOR
        "xor %%dl, %%dl;"

        "while:"
        "cmp %73, %%esi;"               // se esi è I
        "je i;"
        "jmp o?;"                       // se esi non e' I potrebbe essere O
        "i:"
          "addl %4, %%esi;"
          "cmp %78, %%esi;"             // se esi e' N
          "je in_;"
          "jmp fine3;"
          "in_:"
            "addl %8, %%esi;"
            "cmp %65, %%esi;"           // se esi e' A
            "je in_a;"
            "cmp %66, %%esi;"           // se esi e' B
            "je in_b;"
            "cmp %67, %%esi;"           // se esi e' C
            "je in_c;"
            "jmp fine3;"

            /* SE E' IN A */
            "in_a:"
              "cmp %49, %%al;"             // 52 = '4'
              "je full1a;"
              "jmp inizioa;"
              "full1a:"
              "cmp %51, %%ah;"
              "je full2a;"
              "jmp inizioa;"
              "full2a:"
              "movl %67, %%edi;"
              "addl %4, %%edi;"
              "movl %67, %%edi;"
              "addl %4, %%edi;"
              "movl %45, %%edi;"
              "addl %4, %%edi;"
              "movl %%ah, %%edi;"
              "addl %4, %%edi;"
              "movl %%al, %%edi;"
              "addl %4, %%edi;"
              "movl %45, %%edi;"
              "addl %4, %%edi;"
              "movl %%bh, %%edi;"
              "addl %4, %%edi;"
              "movl %%bl, %%edi;"
              "addl %4, %%edi;"
              "movl %45, %%edi;"
              "addl %4, %%edi;"
              "movl %%ch, %%edi;"
              "addl %4, %%edi;"
              "movl %%cl, %%edi;"
              "addl %4, %%edi;"
              "movl %45, %%edi;"
              "addl %4, %%edi;"
              "movl %49, %%edi;"
              "addl %4, %%edi;"
              "movl %48, %%edi;"
              "addl %4, %%edi;"
              "movl %48, %%edi;"
              "addl %4, %%edi;"
              "movl %92, %%edi;"
              "addl %4, %%edi;"
              "movl %110, %%edi;"
              "jmp fine4;"

              "inizioa:"
              "movl %79, %%edi;"            // 79 = 'O'
              "addl %4, %%edi;"
              "movl %67, %%edi;"            // 67 = 'C'
              "addl %4, %%edi;"
              "movl %45, %%edi;"            // 45 = '-'
              "addl %4, %%edi;"

              "cmp %57, %%al;"              // 57 = '9'
              "je riportoa;"
              "inc %%al;"
              "jmp savea1;"
              "riportoa:"
                "movl %48, %%al;"           // 48 = '0'
                "inc %%ah;"
              "savea1:"
                "movl %%ah, %%edi;"
                "addl %4, %%edi;"
                "movl %%al, %%edi;"
                "addl %4, %%edi;"
                "movl %45, %%edi;"
                "addl %4, %%edi;"
                "movl %%bh, %%edi;"
                "addl %4, %%edi;"
                "movl %%bl, %%edi;"
                "addl %4, %%edi;"
                "movl %45, %%edi;"
                "addl %4, %%edi;"
                "movl %%ch, %%edi;"
                "addl %4, %%edi;"
                "movl %%cl, %%edi;"
                "addl %4, %%edi;"
                "movl %45, %%edi;"
                "jmp inizio3;"
                
              "jmp fine4;"

            /* SE E' IN B */
            "in_b:"
              "cmp %49, %%bl;"             // 52 = '4'
              "je full1b;"
              "jmp iniziob;"
              "full1b:"
              "cmp %51, %%bh;"
              "je full2b;"
              "jmp iniziob;"
              "full2b:"
              "movl %67, %%edi;"
              "addl %4, %%edi;"
              "movl %67, %%edi;"
              "addl %4, %%edi;"
              "movl %45, %%edi;"
              "addl %4, %%edi;"
              "movl %%ah, %%edi;"
              "addl %4, %%edi;"
              "movl %%al, %%edi;"
              "addl %4, %%edi;"
              "movl %45, %%edi;"
              "addl %4, %%edi;"
              "movl %%bh, %%edi;"
              "addl %4, %%edi;"
              "movl %%bl, %%edi;"
              "addl %4, %%edi;"
              "movl %45, %%edi;"
              "addl %4, %%edi;"
              "movl %%ch, %%edi;"
              "addl %4, %%edi;"
              "movl %%cl, %%edi;"
              "addl %4, %%edi;"
              "movl %45, %%edi;"
              "addl %4, %%edi;"
              "movl %48, %%edi;"
              "addl %4, %%edi;"
              "movl %49, %%edi;"
              "addl %4, %%edi;"
              "movl %48, %%edi;"
              "addl %4, %%edi;"
              "movl %92, %%edi;"
              "addl %4, %%edi;"
              "movl %110, %%edi;"
              "jmp fine4;"

              "iniziob:"
              "movl %79, %%edi;"            // 79 = 'O'
              "addl %4, %%edi;"
              "movl %67, %%edi;"            // 67 = 'C'
              "addl %4, %%edi;"
              "movl %45, %%edi;"            // 45 = '-'
              "addl %4, %%edi;"

              "cmp %57, %%bl;"              // 57 = '9'
              "je riporto;"
              "inc %%bl;"
              "jmp saveb1;"
              "riporto:"
                "movl %48, %%bl;"           // 48 = '0'
                "inc %%bh;"
              "save1:"
                "movl %%ah, %%edi;"
                "addl %4, %%edi;"
                "movl %%al, %%edi;"
                "addl %4, %%edi;"
                "movl %45, %%edi;"
                "addl %4, %%edi;"
                "movl %%bh, %%edi;"
                "addl %4, %%edi;"
                "movl %%bl, %%edi;"
                "addl %4, %%edi;"
                "movl %45, %%edi;"
                "addl %4, %%edi;"
                "movl %%ch, %%edi;"
                "addl %4, %%edi;"
                "movl %%cl, %%edi;"
                "addl %4, %%edi;"
                "movl %45, %%edi;"
                "jmp inizio3;"


              "jmp fine4;"
            
            /* SE E' IN C */
            "in_c:"
              "cmp %52, %%cl;"             // 52 = '4'
              "je full1c;"
              "jmp inizioc;"
              "full1c:"
              "cmp %50, %%ch;"
              "je full2c;"
              "jmp inizioc;"
              "full2c:"
              "movl %67, %%edi;"
              "addl %4, %%edi;"
              "movl %67, %%edi;"
              "addl %4, %%edi;"
              "movl %45, %%edi;"
              "addl %4, %%edi;"
              "movl %%ah, %%edi;"
              "addl %4, %%edi;"
              "movl %%al, %%edi;"
              "addl %4, %%edi;"
              "movl %45, %%edi;"
              "addl %4, %%edi;"
              "movl %%bh, %%edi;"
              "addl %4, %%edi;"
              "movl %%bl, %%edi;"
              "addl %4, %%edi;"
              "movl %45, %%edi;"
              "addl %4, %%edi;"
              "movl %%ch, %%edi;"
              "addl %4, %%edi;"
              "movl %%cl, %%edi;"
              "addl %4, %%edi;"
              "movl %45, %%edi;"
              "addl %4, %%edi;"
              "movl %48, %%edi;"
              "addl %4, %%edi;"
              "movl %48, %%edi;"
              "addl %4, %%edi;"
              "movl %49, %%edi;"
              "addl %4, %%edi;"
              "movl %92, %%edi;"
              "addl %4, %%edi;"
              "movl %110, %%edi;"
              "jmp fine4;"

              "inizioc:"
              "movl %79, %%edi;"            // 79 = 'O'
              "addl %4, %%edi;"
              "movl %67, %%edi;"            // 67 = 'C'
              "addl %4, %%edi;"
              "movl %45, %%edi;"            // 45 = '-'
              "addl %4, %%edi;"

              "cmp %57, %%cl;"              // 57 = '9'
              "je riporto;"
              "inc %%cl;"
              "jmp save1;"
              "riporto:"
                "movl %48, %%cl;"           // 48 = '0'
                "inc %%ch;"
              "save1:"
                "movl %%ah, %%edi;"
                "addl %4, %%edi;"
                "movl %%al, %%edi;"
                "addl %4, %%edi;"
                "movl %45, %%edi;"
                "addl %4, %%edi;"
                "movl %%bh, %%edi;"
                "addl %4, %%edi;"
                "movl %%bl, %%edi;"
                "addl %4, %%edi;"
                "movl %45, %%edi;"
                "addl %4, %%edi;"
                "movl %%ch, %%edi;"
                "addl %4, %%edi;"
                "movl %%cl, %%edi;"
                "addl %4, %%edi;"
                "movl %45, %%edi;"
                "inizio3:"
                "addl %4, %%edi;"
                "cmp %49, %%al;"
                "je nexta;"
                "jmp wra0;"
                "nexta:"
                    "cmp %51, %%ah;"
                    "je wra1;"
                    "jmp wra0;"
                "wra0:"
                    "movl %48, %%edi;"
                    "jmp bfull;"
                "wra1:"
                    "movl %49, %%edi;"
                "bfull:"
                "addl %4, %%edi;"
                "cmp %49, %%bl;"
                "je nextb;"
                "jmp wrb0;"
                "nextb:"
                    "cmp %51, %%bh;"
                    "je wrb1;"
                    "jmp wrb0;"
                "wrb0:"
                    "movl %48, %%edi;"
                    "jmp cfull;"
                "wrb1:"
                    "movl %49, %%edi;"
                "cfull:"
                "addl %4, %%edi;"
                "cmp %52, %%cl;"
                "je nextc;"
                "jmp wrc0;"
                "nextc:"
                    "cmp %50, %%ch;"
                    "je wrc1;"
                    "jmp wrc0;"
                "wrc0:"
                    "movl %48, %%edi;"
                    "jmp fineec;"
                "wrc1:"
                    "movl %49, %%edi;"
                "fineec:"
                "movl %92, %%edi;"
                "addl %4, %%edi;"
                "movl %110, %%edi;"
                "addl %4, %%edi;"
                


              "jmp fine4;"

        "fine1:"
          "addl %12, %%esi;"
          "o?:"
          "cmp %79, %%esi;"                 // se esi e' O
          "je o;"
          "jmp fine3;"
          "o:"
            "addl %4, %%esi;"
            "cmp %85, %%esi;"               // se esi e' U
            "je ou;"
            "jmp fine3;"
            "ou:"
              "addl %4, %%esi;"
              "cmp %84, %%esi;"             // se esi e' T
              "je out_;"
              "jmp fine3;"
              "out_:"
                "addl %8, %%esi;"
                "cmp %65, %%esi;"           // se esi e' A
                "je out_a;"
                "cmp %66, %%esi;"           // se esi e' B
                "je out_b;"
                "cmp %67, %%esi;"           // se esi e' C
                "je out_c;"
                "jmp fine3;"

                /* SE E' OUT A */
                "out_a:"
                  "nop;"
                  "jmp fine4;"

                /* SE E' OUT B */
                "out_b:"
                  "nop;"
                  "jmp fine4;"

                /* SE E' OUT C */
                "out_c:"
                  "nop;"
                  "jmp fine4;"


      "fine3:"                              // fine3 stampa risultato invariato   
        "addl %4, %%edi;"
        "movl %67, %%edi;"
        "addl %4, %%edi;"
        "movl %67, %%edi;"
        "addl %4, %%edi;"
        "movl %45, %%edi;"
        "addl %4, %%edi;"
        "movl %%ah, %%edi;"
        "addl %4, %%edi;"
        "movl %%al, %%edi;"
        "addl %4, %%edi;"
        "movl %45, %%edi;"
        "addl %4, %%edi;"
        "movl %%bh, %%edi;"
        "addl %4, %%edi;"
        "movl %%bl, %%edi;"
        "addl %4, %%edi;"
        "movl %45, %%edi;"
        "addl %4, %%edi;"
        "movl %%ch, %%edi;"
        "addl %4, %%edi;"
        "movl %%cl, %%edi;"
        "addl %4, %%edi;"
        "movl %45, %%edi;"
        "addl %4, %%edi;"               
        "jmp inizio3;"
        "jmp fine4;"
        
      "fine4:"                              // fine4 va alla riga successiva e torna su
        "addl %4, %%esi;"                   // se non e' la fine della stringa '\0'
        "cmp %92, %%esi;"
        "je fine_string;"
        "addl %8, %%esi;"
        "jmp while;"
        "fine_string:"
          "addl %4, %%esi"
          "cmp %48, %%esi;"
          "je fine_while;"
          "addl %4, %%esi;"
          "jmp while;"
        // FINE WHILE
        "finewhile:"
          "nop;"

            

      : "=r" (bufferout_asm)
      : "r" (bufferin), "r" (bufferout_asm)
    );
    

    toc_asm = current_timestamp();

  	long long asm_time_in_nanos = toc_asm - tic_asm;

    /* FINE ELABORAZIONE ASM */


    printf("C time elapsed: %lld ns\n", c_time_in_nanos);
    printf("ASM time elapsed: %lld ns\n", asm_time_in_nanos);

    /* Salvataggio dei risultati ASM */
  	FILE *outputFile;
    outputFile = fopen (argv[2], "w");
    fprintf (outputFile, "%s", bufferout_asm);
    fclose (outputFile);

    return 0;
}