/* 
 * File:   main.c
 * Author: Maxim Veksler 303856983
 *
 * Created on December 17, 2009, 9:39 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "complex.h"
#include "messages.h"
#include "maindefs.h"

static int errno;

static Complex A;
static Complex B;
static Complex C;
static Complex D;
static Complex E;
static Complex F;



static void halt();
static void help();





/* extract from the input the next complex number to be used by string matching
 *  input: The input string that was types by the user
 *  output: pointer to the complex variable to be used, if not found then NULL */
static Complex* __getComplex(char *input) {
    char *pch;

    pch = strtok(input, TOK_INPUT);

    if(pch == NULL || strlen(pch) != 1 || !(pch[0] >= 'A' && pch[0] <= 'F')) {
        fprintf(stderr, INVALID_VARIABLE_NAME);
        return NULL;
    } else {
        switch (pch[0]) {
            case 'A' : return &A;
            case 'B' : return &B;
            case 'C' : return &C;
            case 'D' : return &D;
            case 'E' : return &E;
            case 'F' : return &F;
        }
    }

    return NULL;
}


/* extract from the input a double number as was typed by the user
 *  input: The input string that was types by the user
 *  output: double if not found then 0.0 and errno is set to NO_NUMBER_FOUND */
static double __getDouble(char *input, char* info_TargetParameterName) {
    char *pch;

    errno = NO_ERROR;

    pch = strtok(input, TOK_INPUT);

    if(pch == NULL) {
        errno = NO_NUMBER_FOUND;
        fprintf(stderr, "%s %s %s", WRONG_PARAMETERS, info_TargetParameterName, NO_DOUBLE_VALUE_FOUND);
        return ERROR_DOUBLE_RETURN_VALUE;
    } else {
        /* The next block verifies we are dealing with valid floating point
         * number representation, note we do not support scientific E notation...
         */
        char *c = pch;

	/* First make sure to chup off the +/- signs */
        if(*c == '+' || *c == '-') {
            c++;
        }

        while((*c >= '0' && *c <= '9')) {
           c++;
        }

        if(*c != '.') { 
            if(*c != '\0') { /* If number contains no \. then it must end here, otherwise it's an error */
                errno = NO_NUMBER_FOUND;
                fprintf(stderr, "%s %s %s", WRONG_PARAMETERS, info_TargetParameterName, NO_DOUBLE_VALUE_FOUND);
                return ERROR_DOUBLE_RETURN_VALUE;
            }
        } else { /* We found a number in the format [[:digit:]]+\. */
            c++;

            while((*c >= '0' && *c <= '9')) {
                c++;
            }

            if(*c != '\0') {
                errno = NO_NUMBER_FOUND;
                fprintf(stderr, "%s %s %s", WRONG_PARAMETERS, info_TargetParameterName, NO_DOUBLE_VALUE_FOUND);
                return ERROR_DOUBLE_RETURN_VALUE;
            }
        }

    }

    return atof(pch);

}

static void read_comp_integration(char* input) {
    Complex *p1;
    double d1;
    double d2;

    /* char holds 1 variable name, 2 float... */
    #if DEBUG
        printf("add_comp %s\n", input);
    #endif

    p1 = __getComplex(input);
    if(p1 != NULL) {
         d1 = __getDouble(NULL, "second");
         if(errno == NO_NUMBER_FOUND) {
             return;
         }

         d2 = __getDouble(NULL, "third");
         if(errno == NO_NUMBER_FOUND) {
             return;
         }

         read_comp(p1, d1, d2);
    }
}

static void print_comp_integration(char *input) {
    Complex *p;

    /* Char holds variable name... */
    #if DEBUG
        printf("print_comp_integration %s\n", input);
    #endif

    p = __getComplex(input);

    if(p != NULL) {
        print_comp(p);
    }
}

static void add_comp_integration(char *input) {
    Complex *p1;
    Complex *p2;

    /* char holds 2 variable names... */
    #if DEBUG
        printf("add_comp %s\n", input);
    #endif

    p1 = __getComplex(input);
    if(p1 != NULL) {
        p2 = __getComplex(NULL);

        if(p2 != NULL) {
            add_comp(p1, p2);
        } /*if(p2 != NULL)*/
    } /*if(p1 != NULL)*/
} /*add_comp*/

static void sub_comp_integration(char *input) {
    Complex *p1;
    Complex *p2;

    /* char holds 2 variable names... */
    #if DEBUG
        printf("sub_comp %s\n", input);
    #endif

    p1 = __getComplex(input);
    if(p1 != NULL) {
        p2 = __getComplex(NULL);

        if(p2 != NULL) {
            sub_comp(p1, p2);
        }
    }
}

static void mult_comp_real_integration(char *input) {
    Complex *p1;
    double d;

    /* char holds 1 variable, 1 float*/
    #if DEBUG
        printf("multi_comp_real %s\n", input);
    #endif


    p1 = __getComplex(input);
    if(p1 != NULL) {
         d = __getDouble(NULL, "second");
         if(errno == NO_NUMBER_FOUND) {
             return;
         }
    }

    mult_comp_real(p1, d);
}

static void mult_comp_img_integration(char *input) {
    Complex *p1;
    double d;

    /* char holds 1 variable, 1 float imaginary*/
    #if DEBUG
        printf("multi_comp_img %s\n", input);
    #endif


    p1 = __getComplex(input);
    if(p1 != NULL) {
         d = __getDouble(NULL, "second");
         if(errno == NO_NUMBER_FOUND) {
             return;
         }
    }

    mult_comp_img(p1, d);
}

static void mult_comp_comp_integration(char *input) {
    Complex *p1;
    Complex *p2;

    /* char holds 2 variable */
    #if DEBUG
        printf("multi_comp_comp %s\n", input);
    #endif

    p1 = __getComplex(input);
    if(p1 != NULL) {
        p2 = __getComplex(NULL);

        if(p2 != NULL) {
            mult_comp_comp(p1, p2);
        }
    }
}

static void abs_comp_integration(char *input) {
    Complex *p;

    /* char holds 1 variable */
    #if DEBUG
        printf("abs_comp %s\n", input);
    #endif

    p = __getComplex(input);

    if(p != NULL) {
        abs_comp(p);
    }

}


static conv_t conversion_array[] = {
    {"read_comp", read_comp_integration, "<reg>,<float1>,<float2> - Set complex <reg> to value <float1> + (<float2>)i"},
    {"print_comp", print_comp_integration, "<reg> - Print complex <reg> value"},
    {"add_comp", add_comp_integration, "<reg1>,<reg2>- Add complex <reg1> to <reg2> and print the result"},
    {"sub_comp", sub_comp_integration, "<reg1>,<reg2> - Subtract complex <reg1> from <reg2> and print the result"},
    {"mult_comp_real", mult_comp_real_integration, "<reg>,<float>- Multiply complex <reg> with real <float> and print the result"},
    {"mult_comp_img", mult_comp_img_integration, "<reg>,<float> - Multiply complex <reg> with imaginary <float> and print the result"},
    {"mult_comp_comp", mult_comp_comp_integration, "<reg1>,<reg2> - Multiply complex <reg1> with complex <reg2> and print the result"},
    {"abs_comp", abs_comp_integration, "<reg> - Calculate absolute value of <reg> and print the result"},
    {NULL, NULL, NULL},
};


/*
 * Loop on user input, Read user command and respond with proper function call 
 * if appropreiate function was found, else print informative error message
 */
int main(int argc, char** argv) {
    char userInput[USER_INPUT_SIZE];
    char *pch;

    conv_t *dynaFuncHandler;
    
    printf(CALCULATOR_HEADER);

    while(TRUE) {
        printf(PLEASE_ENTER_COMMAND);
        fgets(userInput, USER_INPUT_SIZE, stdin);
        pch = strtok(userInput, TOK_INPUT);


        if(pch != NULL) {
            /* Check if it's time to die */
            if(strncmp(HALT_FUNCTION_NAME, pch, 4 /*ester egg*/) == 0) {
                halt();
            } else if(strncmp(HELP_FUNCTION_NAME, pch, 4) == 0) {
                help();
                continue;
            }

            /* Dynamically seek (&find) correct fuction to call
             * We stop either on dynaFuncHandler->function_name == NULL
             * or on match strcmp(pch,  dynaFuncHandler->function_name) == 0
             */
            for(dynaFuncHandler = conversion_array;  dynaFuncHandler->function_name && strcmp(pch,  dynaFuncHandler->function_name); dynaFuncHandler++);

            /* If we have found a function at this name */
            if(dynaFuncHandler->function_name) {
                /* We want to pass the next location after the function name in the general user input string */
                dynaFuncHandler->pt2func(&userInput[strlen(pch)+1]);
            } else {
                fprintf(stderr, NOT_VALID_COMMAND);
            }
        } else {
            fprintf(stderr, NO_COMMAND_INPUT);
            help();
        }

        printf("\n");
    }

    printf("\n%s", userInput);
    return EXIT_SUCCESS;
}

static void help() {
	conv_t *dynaFuncHandler;

        printf("Following Complex number registers are defined: A,B,C,D,E,F\n");
        printf("\n");
	printf("These operations available:\n");

	for(dynaFuncHandler = conversion_array;  dynaFuncHandler->function_name; dynaFuncHandler++) {
		printf("\t%s %s\n", dynaFuncHandler->function_name, dynaFuncHandler->helpText);
	}

	printf("\n");
        printf("halt - To exit the application.\n");
}

static void halt() {
    /* Easter egg code... */
    char *pch;
    int jokeIndex = 0;
    char *jokes[] = { "What?!?!? !!!", 
		      "WHAT DO YOU WANT FROM ME???",
		      "Ya neit speak your language",
                      "What do you think I am? a Telepathic vending machine?",
		      "Stop it!",
                      "Go away!",
                      "Leave me alone.",
                      "Dude, I mean it!!",
                      "That's it, You have been telekanisized!!  ( http://www.tapuz.co.il/blog/userBlog.asp?FolderName=orenzarif )"
                   };
    for(pch = strtok(NULL, TOK_INPUT), jokeIndex = 0; pch != NULL && jokeIndex < 9; pch = strtok(NULL, TOK_INPUT), jokeIndex++) {
       printf("\"%s\" Ha? -- %s\n", pch, jokes[jokeIndex]);
    }
    /* Easter egg code ends here... */

    exit(EXIT_SUCCESS);
}
