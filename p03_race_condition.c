#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

int mails = 0;

void* routine() {
    for(int i = 0; i < 1000000; i++){
        mails++;
        // read mails
        // increment
        // write mails
    }
}



int main(int argc, char* argv[]) {
    pthread_t t1, t2;
    if (pthread_create(&t1, NULL, &routine, NULL) != 0) {
        return 1;
    }
    if (pthread_create(&t2, NULL, &routine, NULL) != 0) {
        return 2;
    }
    if (pthread_join(t1, NULL) != 0) {
        return 3;
    }
    if (pthread_join(t2, NULL) != 0) {
        return 4;
    }
    printf("number of mails: %d\n", mails);

    return 0;
}


// Each time this program runs it prints
// mails values which is not necessary same
// to the previous run of program


//                   t1  | t2
// read mails        29  | 23
// increment         29  | 30 
// write mails       30  | 24
//
// t1 and t2 both read mails as 23 initially
// only t1 got chance to execute and t2 was not allowed
// when t2 executed it worked on old values of mails
// which is wrong 

/*
 * Assembly Code of mail
 *
 * .L3:
 *  	movl	mails(%rip), %eax
 *   	addl	$1, %eax
 *	    movl	%eax, mails(%rip)
 *	    addl	$1, -4(%rbp)
 *
 * 
*/