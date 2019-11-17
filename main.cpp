#include <GL/glut.h>
#include <stdio.h>
#include <string>
#include <math.h>
#include <iostream>
#include <typeinfo>
#include "circulos/circulos.h"
#include "aviao/aviao.h"
#include "tiro/tiro.h"
#include "tiros/tiros.h"
#include "bomba/bomba.h"
#include "bombas/bombas.h"
#include "InimigoVoador/InimigoVoador.h"
#include "InimigosVoadores/InimigosVoadores.h"
#include "tinyxml2.h"

using namespace tinyxml2;


//arrays auxiliares
int flags[256];
char nome[1000];
char tipo[50];
char caminhoArq[1000];


//medicao de tempo entre chamadas da funcao idle
GLdouble tempoAtual = 0.0;
GLdouble deltaTempo = 0.0;
GLdouble tempoAnterior = 0.0;


//jogador
float vel;
float v_dec_final;
float v_dec = 0.0;
float velX = 0.5;
float velY = 0.5;
float velTiro = 0.0;


//inimigo
float vel_inimigo;
float velTiro_inimigo = 0.0;
float freqTiro_inimigo = 0.0;


//decolagem
bool decolando = false;
bool decolou = false;
float v_dec_imutavel = 0.0;

//circles
float cx, cy, cr, r0, cx0, cy0, cxArena, cyArena;  //r0 variavel auxiliar para guardar o raio inicial do aviao
std::string fill;
int cid, cjid;

//line
float lx1, ly1, lx2, ly2;
std::string lstyle;
int lid;


//titulo da janela
char titulo[1000];

float num_segs = 360;

//janela
int window_width;
int window_height;

//movimento do mouse
float mouse_x;


//objetos globais
Circulos circulos = Circulos();
Circulo* player;
Circulo* arena;

Aviao plane = Aviao();
InimigosVoadores inimigosvoadores = InimigosVoadores();

Tiros tiros = Tiros();

Bombas bombas = Bombas();

//assinatura da funcao
void drawCirculoMouse(float x_centro, float y_centro, float raio, int num_seg);

void restart();

void display(void) {
    /* Limpar todos os pixels */
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(50);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    gluOrtho2D(cxArena - window_width/2, cxArena + window_width/2, (window_height - cyArena) - window_height/2, (window_height - cyArena) + window_height/2);

    //desenhando objetos
    for(Circulo c : circulos.getLista()){
        if(!c.estaMorto()){
            if(c.getFill().compare("green") == 0){  //desenha a linha antes do aviao para ele ficar por cima
                //desenho da line
                glColor3f(0.0, 0.0, 0.0);
                glBegin(GL_LINES);
                    glVertex2f(lx1, window_height - ly1);
                    glVertex2f(lx2, window_height - ly2);
                glEnd();
                //c.drawCirculo();
                if(!decolando && !decolou){
                    plane.setThetaPlane(atan2((window_height-ly2)-(window_height-ly1), lx2-lx1));
                }
                bombas.drawBombas(arena);
                plane.desenhaAviao(c.getXCoord(), c.getYCoord(), c.getRaio(), 'j');
                tiros.drawTiros(arena);
            } else if(c.getFill().compare("red") == 0){
                InimigoVoador* aux = inimigosvoadores.getInimigoVoadorById(c.getId());
                if(aux->getId() != -1){
                    aux->desenhaInimigoVoador(c.getXCoord(), c.getYCoord());
                }
            } else {
                c.drawCirculo();
            }
        }
    }

    /* Nao esperar! */
    glFlush();
}

void init(void) {
    /* selecionar cor de fundo (preto) */
    glClearColor(0.0, 0.0, 0.0, 0.0);

    /* inicializar sistema de viz. */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);

}

//funcao para tratar click do mouse
void mouse(int button, int state, int x, int y) {
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && !plane.getPerdeu()) {
        //tiro
        if(decolou){
            tiros.addTiro(tiros.getIncrementingNth(), player->getXCoord(), player->getYCoord(), player->getRaio(), 
                            plane.getThetaPlane(), plane.getThetaCanhao(), v_dec*velTiro, 'j');
        }
	}
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && !plane.getPerdeu()) {
        //bomba
        if(decolou){
            bombas.addBomba(bombas.getIncrementingNth(), player->getXCoord(), player->getYCoord(), player->getRaio(), 
                            plane.getThetaPlane(), v_dec);
        }
	}
    // glutPostRedisplay();
}

//funcao para tratar movimento do mouse
void motion( int x, int y ) {
    if(decolou && !plane.getPerdeu()){
        if(x > mouse_x){
            plane.rotateCanhao(-2*M_PI/3*(deltaTempo/100));
        } else if(x < mouse_x){
            plane.rotateCanhao(2*M_PI/3*(deltaTempo/100));
        } else {
            //
        }
        mouse_x = x;
        // glutPostRedisplay();
    }
}

void drag(int x, int y){
    if(decolou && !plane.getPerdeu()){
        if(x > mouse_x){
            plane.rotateCanhao(-2*M_PI/3*(deltaTempo/100));
        } else if(x < mouse_x){
            plane.rotateCanhao(2*M_PI/3*(deltaTempo/100));
        } else {
            //
        }
        mouse_x = x;
        // glutPostRedisplay();
    }
}


void keyPress(unsigned char key, int x, int y) {
	flags[key] = 1;
}

void keyUp(unsigned char key, int x, int y) {
	flags[key] = 0;
}

void idle(void) {
    tempoAtual = glutGet(GLUT_ELAPSED_TIME);
    deltaTempo = tempoAtual - tempoAnterior;
    tempoAnterior = tempoAtual;
    if(decolou){

        if(flags['r'] == 1){
            restart();
        }

        if(plane.getPerdeu()){
            return;
        }

        //o motivo de recalcular as velocidades eh para evitar de caso por algum arredondamento
        //deltaTempo tenha dado zero ao fim da decolagem (aonde tem este calculo), entao,
        //outra vez nao vai ser pequeno suficiente para a maquina arredondar para zero, e assim,
        //nao fique com a velocidade igual a zero
        v_dec_final = v_dec * vel * (deltaTempo/1000);
        velX = v_dec_final * cos(plane.getThetaPlane()*3.14159265/180);
        velY = v_dec_final * sin(plane.getThetaPlane()*3.14159265/180);

        // inimigosvoadores.moverInimigos(deltaTempo);
        circulos.moverInimigos(arena, v_dec_imutavel * deltaTempo/1000, inimigosvoadores);
        inimigosvoadores.moverHelicesInimigos(v_dec_imutavel * deltaTempo/1000);
        inimigosvoadores.virarInimigos(deltaTempo/1000);
        // inimigosvoadores.atirar(&tiros, tempoAtual);
        if(inimigosvoadores.atirar(tempoAtual)){
            std::vector<Circulo> list_circulo = circulos.getLista();
            for(int i = 0; i < list_circulo.size(); i++){
                if(!list_circulo[i].estaMorto() && list_circulo[i].getFill().compare("red") == 0){
                    InimigoVoador* aux = inimigosvoadores.getInimigoVoadorById(list_circulo[i].getId());
                    tiros.addTiro(tiros.getIncrementingNth(), list_circulo[i].getXCoord(), list_circulo[i].getYCoord(), list_circulo[i].getRaio(), 
                                aux->getThetaMyPlane(), aux->getThetaMyCanhao(), v_dec_imutavel * inimigosvoadores.getVelTiro(), 'i');
                }
            }
        }
        // circulos.teletransporteInimigos(arena, inimigosvoadores, v_dec_imutavel * deltaTempo/1000);

        if(decolou && !circulos.colideComInimigo(player->getXCoord(), player->getYCoord()+velY, player->getRaio())){
	    	player->moveY(velY);
            arena->estaTotalmenteDentro(player, &plane, "cima", velY);
        }

        if(decolou && !circulos.colideComInimigo(player->getXCoord()+velX, player->getYCoord(), player->getRaio())){
	    	player->moveX(velX);
            arena->estaTotalmenteDentro(player, &plane,"direita", velX);
        }

        plane.rotateHelice(sqrt(pow(velX, 2) + pow(velY, 2)), player->getRaio());
        tiros.moverTiros(deltaTempo/1000);
        bombas.moverBombas(deltaTempo/1000);

        for(int i = 0; i < circulos.getLista().size(); i++){
            if(circulos.getLista()[i].getFill().compare("red") == 0 && tiros.aviaoBaleado(&circulos.getLista()[i], 'j')){
                circulos.matarCirculoById(circulos.getLista()[i].getId(), circulos.getLista()[i].getXCoord(), circulos.getLista()[i].getYCoord(), "red");
            }
            if(circulos.getLista()[i].getFill().compare("orange") == 0 && bombas.baseBombardeada(&circulos.getLista()[i])){
                std::cout << "aqui" << std::endl;
                circulos.matarCirculoById(circulos.getLista()[i].getId(), circulos.getLista()[i].getXCoord(), circulos.getLista()[i].getYCoord(), "orange");
            }
        }

        if(!plane.getPerdeu() && (circulos.colideComInimigo(player->getXCoord(), player->getYCoord()+velY, player->getRaio()) || tiros.aviaoBaleado(player, 'i'))){
            plane.setPerdeu(true);
            tiros.pararTiros();
            bombas.pararBombas();
            std::cout << "Voce perdeu, fim de jogo!\nPressione r para recomecar." << std::endl;
        }
	    if(flags['a'] == 1) {
            plane.rotatePlane((M_PI/2)*(deltaTempo/1000));
	    }

	    if(flags['d'] == 1) {
            plane.rotatePlane(-(M_PI/2)*(deltaTempo/1000));
	    }

        if(flags['+'] == 1){
            v_dec += sqrt(pow(((lx2-lx1) / 8) * (deltaTempo/1000), 2) + pow((((window_height - ly2) - (window_height - ly1)) / 8) * (deltaTempo/1000), 2));
        }

        if(flags['-'] == 1){
            v_dec -= sqrt(pow(((lx2-lx1) / 8) * (deltaTempo/1000), 2) + pow((((window_height - ly2) - (window_height - ly1)) / 8) * (deltaTempo/1000), 2));
            if(v_dec <= 0){
                v_dec = 0;
            }
        }


        // tiros.moverTiros(deltaTempo/1000);
    } else if(decolando) {

        if(flags['r'] == 1){
            restart();
        }

        float distanciaLine = sqrt(pow((lx2 - lx1),2) + pow(((window_height - ly2) - (window_height - ly1)), 2));
        float distPlayerLine = sqrt(pow((player->getXCoord() - lx1),2) + pow((player->getYCoord() - (window_height - ly1)), 2));
        velX += ((lx2-lx1) / 8) * (deltaTempo/1000); //vx = vx0 + a*t
        velY += (((window_height - ly2) - (window_height - ly1)) / 8) * (deltaTempo/1000); //vy = vy0 + a*t
        player->moveX(velX*(deltaTempo/1000));
        player->moveY(velY*(deltaTempo/1000));
        v_dec = sqrt(pow(velX,2) + pow(velY,2));
        

        if(distPlayerLine >= distanciaLine/2){
            player->aumentarRaio(v_dec * (deltaTempo/1000) * (r0 / (distanciaLine/2)));
        }

        if(distPlayerLine >= distanciaLine){
            decolando = false;
            decolou = true;
            v_dec_final = v_dec * vel * (deltaTempo/1000);
            velX = v_dec_final * cos(45.0*3.14159265/180);
            velY = v_dec_final * sin(45.0*3.14159265/180);
            v_dec_imutavel = v_dec;
            inimigosvoadores.setTempoControleTiro(tempoAtual);
            if(decolou){
                std::cout << "decolou: " << "sim - instante: " << tempoAtual/1000 << std::endl;
            }
        }

        plane.rotateHelice(sqrt(pow(velX, 2) + pow(velY, 2)), player->getRaio());
	} else {
        if(flags['u'] == 1) {
            decolando = true;
        }
    }

	glutPostRedisplay();
}

void restart(){
    velX = 0.0;
    velY = 0.0;
    v_dec = 0.0;
    v_dec_final = 0.0;
    v_dec_imutavel = 0.0;
    tiros.limparTiros();
    bombas.limparBombas();
    bombas.resetNth();
    plane.setPerdeu(false);
    plane.setThetaCanhao(0.0);
    plane.setThetaHelice(0.0);
    decolou = false;
    decolando = false;
    inimigosvoadores.setInitConditions();
    circulos.setInitalPositions();
    player->setCoords(cx0, cy0);
    player->setRaio(r0);
    std::cout << "\\------------------------------------------------//" << std::endl;
    std::cout << "\\------------------------------------------------//" << std::endl;
    std::cout << "\\---------------------Restart Game---------------//" << std::endl;
}

//leitura do XML atraves do tinyxml2
bool readConfigXML(const char* caminho_pastas){
    //preparando caminho completo para leitura
    char caminho_completo[1000];
    strcpy(caminho_completo, caminho_pastas);
    strcat(caminho_completo, "config.xml");

    //lendo arquivo
    XMLDocument xmlDoc;
    bool leitura_fail = xmlDoc.LoadFile(caminho_completo);

    if(!leitura_fail){
        //aplicacao
        XMLNode* pRoot = xmlDoc.FirstChild();

        XMLElement * pElement = pRoot->FirstChildElement("arquivoDaArena")->FirstChildElement("nome");
        const char* str = pElement->GetText();
        strcpy(nome , str);

        pElement = pRoot->FirstChildElement("arquivoDaArena")->FirstChildElement("tipo");
        str = pElement->GetText();
        strcpy(tipo, str);

        pElement = pRoot->FirstChildElement("arquivoDaArena")->FirstChildElement("caminho");
        str = pElement->GetText();
        strcpy(caminhoArq, str);

        pElement = pRoot->FirstChildElement("jogador");
        pElement->QueryFloatAttribute("vel", &vel);
        pElement->QueryFloatAttribute("velTiro", &velTiro);

        pElement = pRoot->FirstChildElement("inimigo");
        pElement->QueryFloatAttribute("freqTiro", &freqTiro_inimigo);
        pElement->QueryFloatAttribute("vel", &vel_inimigo);
        pElement->QueryFloatAttribute("velTiro", &velTiro_inimigo);

        inimigosvoadores.setVel(vel_inimigo);
        inimigosvoadores.setVelTiro(velTiro_inimigo);
        inimigosvoadores.setFreqTiro(freqTiro_inimigo);

        std::cout << "nome: " << nome << std::endl;
        std::cout << "tipo: " << tipo << std::endl;
        std::cout << "caminho: " << caminhoArq << std::endl;
        std::cout << "vel: " << vel << std::endl;
        std::cout << "velTiro: " << velTiro << std::endl;
        std::cout << "freqTiro: " << freqTiro_inimigo << std::endl;
        std::cout << "velInimigo: " << vel_inimigo << std::endl;
        std::cout << "velTiroInimigo: " << velTiro_inimigo << std::endl;
        std::cout << "iniciando leitura do svg" << std::endl;
        return true;
    } else {
        std::cout << "Erro de leitura do arquivo config.xml. Verifique o caminho passado." << std::endl;
        return false;
    }

}

//leitura do SVG atraves do tinyxml2
bool readSVG(const char* caminho, char* nome, char* tipo){
    //preparando caminho completo para leitura
    char caminho_completo[1000];
    strcpy(caminho_completo, caminho);
    strcat(caminho_completo, nome);
    strcat(caminho_completo, ".");
    strcat(caminho_completo, tipo);
    std::cout << "caminho SVG: " << caminho_completo << std::endl;

    //lendo arquivo
    XMLDocument xmlDoc;
    bool leitura_fail = xmlDoc.LoadFile(caminho_completo);

    if(!leitura_fail){
        //svg
        XMLNode* pRoot = xmlDoc.FirstChildElement("svg");

        XMLElement * pElement = pRoot->FirstChildElement();
        std::cout << "iniciando loop de leitura de circles" << std::endl;
        while(pElement != NULL){
            std::cout << "elemento - " << pElement->Name() << std::endl;
            if(strcmp(pElement->Name(), "circle") == 0 && strncmp(pElement->Name(), "circle", strlen("circle")) == 0){
                pElement->QueryFloatAttribute("cx", &cx);
                std::cout << "cx: " << cx << std::endl;
                pElement->QueryFloatAttribute("cy", &cy);
                std::cout << "cy: " << cy << std::endl;
                pElement->QueryFloatAttribute("r", &cr);
                std::cout << "r: " << cr << std::endl;
                fill = pElement->Attribute("fill");
                std::cout << "fill: " << fill << std::endl;
                pElement->QueryIntAttribute("id", &cid);
                std::cout << "id: " << cid << std::endl;
                if(fill.compare("blue") == 0){
                    window_height = 2*cr;
                    window_width = 2*cr;
                    cxArena = cx;
                    cyArena = cy;
                }
                if(fill.compare("green") == 0){
                    cjid = cid;
                    r0 = cr;
                    cx0 = cx;
                    cy0 = window_height - cy;
                }
                if(fill.compare("red") == 0){
                    inimigosvoadores.addInimigoVoador(cid, cr, vel_inimigo, velTiro_inimigo, freqTiro_inimigo);
                }
                circulos.addCirculo(cr, cx, window_height - cy, num_segs, fill, cid);
            } else if(strcmp(pElement->Name(), "line") == 0 && strncmp(pElement->Name(), "line", strlen("line")) == 0){
                pElement->QueryFloatAttribute("x1", &lx1);
                std::cout << "x1: " << lx1 << std::endl;
                pElement->QueryFloatAttribute("y1", &ly1);
                std::cout << "y1: " << ly1 << std::endl;
                pElement->QueryFloatAttribute("x2", &lx2);
                std::cout << "x2: " << lx2 << std::endl;
                pElement->QueryFloatAttribute("y2", &ly2);
                std::cout << "y2: " << ly2 << std::endl;
                lstyle = pElement->Attribute("style");
                std::cout << "style: " << lstyle << std::endl;
                pElement->QueryIntAttribute("id", &lid);
                std::cout << "id: " << lid << std::endl;
            }
            pElement = pElement->NextSiblingElement();
        }
        return true;
    } else {
        std::cout << "Erro de leitura. Verifique se o arquivo .svg esta no caminho indicado pelo config.xml." << std::endl;
        return false;
    }
}


int main(int argc, char** argv) {
    if(argv[1] !=  NULL){
        if(readConfigXML(argv[1])){
            if(readSVG(caminhoArq, nome, tipo)){
                player = circulos.getCirculoById(cjid);
                arena = circulos.getCirculoByColor("blue");
                inimigosvoadores.initThetaHelices();
                inimigosvoadores.initThetaCanhao();
                glutInit(&argc, argv);
                glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
                glutInitWindowSize(window_width, window_height);
                glutInitWindowPosition(10, 10);
                glutCreateWindow("TC3");
                init();
                glutDisplayFunc(display);
 	            glutKeyboardFunc(keyPress);
	            glutKeyboardUpFunc(keyUp);
	            glutIdleFunc(idle);
                glutMouseFunc(mouse);
                glutMotionFunc(drag);
                glutPassiveMotionFunc(motion);
                glutMainLoop();

                /* C ANSI reque que main retorne um inteiro */
                return 0;
            }
        }
    } else {
        std::cout << "Caminho nao passado por parametro" << std::endl;
    }
    
}