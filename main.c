#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int mensageirosV = 5, mensageirosA = 10, perdeu = 0, timeParcial = 0,tmAzul,tmVer;
int timeTotal=0, horarioAceito = 0, capturaV = 0, capturaA = 0,AzulACaminho=0,i=0;
int horario = 0;

void vermelho_envia();
void azul_envia();

void enviar_mensageiro(int cor){ //cor = 0 -> azul cor = 1 -> vermelho
     //Gerar um número aleatório para o tempo de viajem do mensageiro
    int tempoMens = rand() % 601 + 3600; 
    if(cor==0){ //Ve se é vermelho ou azul   
        mensageirosA--;//Diminui um azul
        if(capturaA==1){ //Ve se o azul a ser enviado vai ser capturado
            tempoMens = 4201;//Se ele foi capturado, o azul espera esse tempo e envia outro
            printf("\nO %dº mensageiro azul foi enviado\n",(10-mensageirosA));            
            printf("Castelo capturou mensageiro, esperaram 4201 segundos. \n");
        }else{
            printf("\nO %dº mensageiro azul foi enviado  --  Seu tempo foi: %d\n",(10-mensageirosA),tempoMens);
            printf("Castelo não capturou mensageiro\n");
        }
        tmAzul = tempoMens;//Marca o ultimo tempo do azul
        printf("Numero atual de mensageiros azuis: %d\n",mensageirosA);
    }else{
        mensageirosV--;//Diminui um vermelho
        if(capturaV==1){//Ve se o vermelho a ser enviado vai ser capturado
            tempoMens = 12601;//Se ele foi capturado, o vermelho espera esse tempo e envia outro
            printf("\nO %dº mensageiro vermelho foi enviado\n",(5-mensageirosV));    
            printf("Castelo capturou mensageiro, esperaram 12601 segundos. \n");
        }else{
            printf("\nO %dº mensageiro vermelho foi enviado  --  Seu tempo foi: %d\n",(5-mensageirosV),tempoMens);
            printf("Castelo não capturou mensageiro\n");
        }
        printf("Numero atual de mensageiros vermelhos: %d\n",mensageirosV);
        tmVer = tempoMens;//Marca o ultimo tempo do vermelho
    }
    //Acrescenta ao tempo total a viagem do mensageiro
    timeParcial += tempoMens;
    timeTotal += tempoMens;
}

//Função que verifica a partir de um valor aleatório gerado
// se o castelo capturou ou não o mensageiro
int castelo_captura_mensageiro(){
    int porcentagem = rand() % 100;
    porcentagem -= 45;//Subtrai a porcentagem de 45 para ver se o mensageiro foi ou não capturado
    if(porcentagem<=0){//Da negativo ou 0 se foi
        return 1; //Castelo capturou mensageiro        
    }else{
        return 0;//Castelo não capturou mensageiro
    }
}

int azul_impossibilita_horario(){
    int porcentagem = rand() % 100;
    porcentagem -= 1;//Subtrai a porcentagem de 1 para ver se o mensageiro foi ou não capturado
    if(porcentagem<=0){
        printf("\nExercito azul impossibilitou horario\n");
        return 1; //Exercito azul impossibilitou horario
    }else{
        printf("\nExercito azul aceitou horario\n");
        horarioAceito = 1;
        return 0;//Exercito azul aceitou horario
    }
}

void if_mens(){
    if(mensageirosA == 0){//Verifica se eles ficariam sem mensageiros (Não pode)
        printf("\n\nNão restou mais mensageiros azuis.\n");
        perdeu = 1;
    }else{
        capturaA = castelo_captura_mensageiro();//Verifica se capturou
        enviar_mensageiro(0);    
        if(capturaA == 0){//Verifica se capturou
            if(timeParcial>=12601){//Verifica se o tempo ja passou do limite
                azul_envia();
            }else{
                if(horario == 0){//Verifica se o horario foi aceito
                    printf("\n\nO mensageiro azul chegou ao vermelho e informou que o horário foi aceito.\n");
                    //Ganhou a batalha
                }else{
                    vermelho_envia();
                }
            }
        }else{
            azul_envia();//Se foi capturado, envia outro
        }
    }
}

void azul_envia(){
    if(timeParcial>=12601){//Verifica se o tempo passou de 12601       
        if(i==0){
            //O i é para enviar só 1 vez o vermelho quando o tempo passar de 12601
            i=1;
            printf("\n\nTempo passou de 12601...\n");//Vermelho n foi capturado, mas azul sim, vermelho n sabe, ent envia outro.
            AzulACaminho = 1; //Para mesmo que o vermelho seje capturado, o fluxo volte aqui
            vermelho_envia();
        }else{
            if(tmVer<=tmAzul){//Verifica se otempo do vermelho foi menor que o do azul para ver quem chegou primeiro
                if_mens();
            }else{
                printf("\n\nO azul chegou ao vermelho e informou que o horário foi aceito.\n");
                //Ganhou
            }
        }
    }else{
         //horario retorna se o azul negou ou não o horario determinado
        if(horarioAceito != 1){//Vericida se o horario ja foi aceito antes, se sim, n precisa mais verificar
            horario = azul_impossibilita_horario();
        }
        if_mens();  
    } 
}

void vermelho_envia(){   
    timeParcial = 0;
    if(mensageirosV == 0){ //Se só restar 1 mensageiro o vermelho perde
        printf("\n\nNão restou mais mensageiros vermelhos.\n");
        perdeu = 1;
    }else{
        //Verifica se o castelo capturou o mensageiro na viagem
        capturaV = castelo_captura_mensageiro();
        enviar_mensageiro(1); //Enviar mensageiro (1) significa que é vermelho

        if(capturaV == 0){      
            azul_envia();//Se n capturou vermelho, significa que ele chegou no azul, ent entra na função azul_envia   
        }else{
            if(AzulACaminho==1){
                tmVer = 4201; //Declara isso para no azul envia o azul conseguir chegar primeiro, já que o vermelho foi capturado 
                //Se o azul já tiver sido enviado e o vermelho não saiba, volta na azul envia
                azul_envia();
            }else{
                vermelho_envia(); //Se capturou, depois de 12601s o vermelho reenvia
            }
        }
    }  
}

int main()
{
    srand(time(NULL));
    printf("%ld",time(NULL));  
    vermelho_envia(); 
    int hora, min, seg;
    hora = timeTotal / 3600;
    min = (timeTotal-hora*3600)/60;
    seg = timeTotal-((hora*3600)+(min*60));  
    if(perdeu==1){
        printf("O exército perdeu a guerra!!\n");
    }else{
        printf("O exército ganhou a guerra!!\n");
    }
    printf("A troca de mensagens demorou: %d seg OU %d:%d:%d\n",timeTotal, hora,min,seg);
    printf("Restou %d mensageiros de exército vermelho.\n",(mensageirosV));
    printf("Restou %d mensageiros de exército azul.\n",(mensageirosA));
    return 0;
}

