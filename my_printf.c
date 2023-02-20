#include<stdio.h>
#include<unistd.h>
#include<stdarg.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>

void bekond(char* dft, int sols, int shaps) {
    if (sols >= shaps) {
        return;
    }

    char vaqtnsha = dft[sols];
    dft[sols] = dft[shaps];
    dft[shaps] = vaqtnsha;
    bekond(dft, sols + 1, shaps - 1);
}

void almatys(char* beknurs) {
    int uzns = strlen(beknurs);
    bekond(beknurs, 0, uzns - 1);
}

char* shymkents(int qizdars, char dtp[], int topp){
    int wh = 0;
    int neg = 0;

    if(qizdars < 0) {
        neg = 1;
        qizdars = -qizdars;
    }

    if(qizdars == 0) {
        dtp[wh++] = '0';
    } else {
        for(; qizdars > 0; qizdars /= topp) {
            int remainder = qizdars % topp;
            if (remainder < 10) {
                dtp[wh++] = '0' + remainder;
            } else {
                dtp[wh++] = 'A' + remainder - 10;
            }
        }
    }

    if (neg) {
        dtp[wh++] = '-';
    }
    dtp[wh] = '\0';

    almatys(dtp);

    return dtp;
}

int bekonur(char eo) {
  return write(1, &eo, 1);
}

void bekonurs(char* kizdars)
{
    for (int sendei = 0; kizdars[sendei] != '\0'; sendei++) {
        bekonur(kizdars[sendei]);
    }
}

void bekon_qr(double aidays) {
    int bek_qws = (int) aidays;
    double balgoy = aidays - bek_qws;
    balgoy *= 10000000;
    int bek_bak = (int) balgoy;

    char b_ast[20];  // assuming the maximum length of integer part is 20
    char m_qor[8];   // assuming the maximum length of fractional part is 7

    shymkents(bek_qws, b_ast, 10);
    bekonurs(b_ast);
    bekonur('.');

    if (bek_bak == 0) {
        bekonur('0');
        bekonur('0');
        bekonur('0');
        bekonur('0');
        bekonur('0');
        bekonur('0');
        bekonur('0');
    } else {
        shymkents(bek_bak, m_qor, 10);
        int uzuns = strlen(m_qor);
        int jk;
        for (jk = 0; jk < 7 - uzuns; jk++) {
            bekonur('0');
        }
        bekonurs(m_qor);
    }
}

int bekon_kaz(va_list mbd, char kizz){
    char eg;
    char *bmd;
    int wf;
    double kl;
    void *wahk;
    
    switch (kizz) {
     
        case 's':
            bmd = va_arg(mbd, char*);
            bekonurs(bmd);
            return strlen(bmd);
            break;

        case 'c':
            eg = (char) va_arg(mbd, int);
            bekonur(eg);
            return 1;
            break;
 
        case 'd':
            wf = va_arg(mbd, int);
            char* bm = (char*) malloc(sizeof(wf) * sizeof(char*));
            bm = shymkents(wf, bm, 10);
            bekonurs(bm);
            return strlen(bm);
            break;

        case 'o':
            wf = va_arg(mbd, int);
            bm = (char*) malloc(sizeof(wf) * sizeof(char*));
            bm = shymkents(wf, bm, 8);
            bekonurs(bm);
            return strlen(bm);
            break;
 
        case 'u':
            wf = va_arg(mbd, int);
            unsigned int t = (unsigned int) wf;
            bm = (char*) malloc(sizeof(t) * sizeof(char*));
            bm = shymkents(t, bm, 10);
            bekonurs(bm);
            return strlen(bm);
            break;
  
        case 'x':
            wf = va_arg(mbd, int);
            bm = (char*) malloc(sizeof(char) * sizeof(wf));
            bm = shymkents(wf, bm, 16);
           
            bekonurs(bm);
            return strlen(bm);
            break;

        case 'f': 
            kl = va_arg(mbd, double);
            bekon_qr(kl);
            break;
      
        case 'p':
            wf = va_arg(mbd, int);           
            char* be = (char*) malloc(sizeof(wahk) * sizeof(char*));  
            be = (char*) &wf;
            bekonurs(be); 
            return strlen(be);
            break;

    } 
    return 0;
}
    


int my_printf(char* formasd, ...) {
    va_list qorsg;
    bool bek_qors = false;
    int bektz = 0;

    va_start(qorsg, formasd);

    for (int fd = 0; formasd[fd] != '\0'; fd++) {
        if (bek_qors) {
            bektz += bekon_kaz(qorsg, formasd[fd]);
            bek_qors = false;
        } else if (formasd[fd] == '%') {
            bek_qors = true;
        } else {
            bekonur(formasd[fd]);
            bektz++;
        }
    }

    va_end(qorsg);

    return bektz;
}
