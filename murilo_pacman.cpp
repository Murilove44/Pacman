#include <SFML/Graphics.hpp>
#include <cstdlib>
#include<ctime>
#include <iostream>

char mapa[15][24] = {
  "11011111111111111111011",
  "12222222222222222222221",
  "12111010011100101110121",
  "12210011001001100100121",
  "12200010000000100001121",
  "12200000222222000000021",
  "12212212110011212121021",
  "11112010100001012121111",
  "22222010110011012122222",
  "11112000000000002121111",
  "12212222222222222121221",
  "12000010011110010000021",
  "12112111001100111211221",
  "12222222222222222222221",
  "11011111111111111111011"
};
int pilula = 110; //numero de pilulas do jogo
int pontos = 0; //armazena a pontuação

int posx = 15; // posicao do PacMan
int posy = 9;

int Fx, Fy;    //posição para o fantasma1, eixo x, eixo y
int Fx2, Fy2;  //posição para o fantasma2, eixo y, eixo y
int Fx3, Fy3;  //posição para o fantasma3, eixo y, eixo y
int Fx4, Fy4;  //posição para o fantasma4, eixo y, eixo y

// direcao de movimento do pacman
bool cima = false;
bool baixo = false;
bool esq = false;
bool dir = false;

// está olhando para a direita?
bool olhadireita = true;
//está olhando pra cima?
bool olhacima = false;
//está olhando pra esquerda?
bool olhaesquerda = false;
//está olhando pra baixo?
bool olhabaixo = false;

//comandos para armazenar a direção do pacman e tornar o movimento dele igual ao do jogo:
bool cima2 = false;
bool baixo2 = false;
bool dir2 = false;
bool esq2 = false;

//condição de parada do jogo (quando o pacman encosta em um fantasma)
bool verifica(int px, int py, int fx, int fy) {
    return (px == fx && py == fy);
}
//escreve uma mensagem no fim do programa se o pacman perde
bool perdeu = false; //inicia afirmando que o jogo não acaba
sf::Font fonte;
sf::Text fimdejogo; 

//escreve uma mensagem no fim do programa se o pacman ganha
bool ganha = false;
sf::Font fonte1;
sf::Text fimdejogo1;

//pontuação do pacman
sf::Text pontuacao;

//bool inicia = true;
sf::Font fonte2;
sf::Text inicia1;

int main() {
    // cria a janela
    sf::RenderWindow window(sf::VideoMode(1150, 750), "Pac-Man");

    if (!fonte.loadFromFile("C:/Users/Sousa/Desktop/INF/fonte/Roboto-Black.ttf")) {  
        std::cout << "Erro lendo a fonte\n";
        return 0;
    }
    srand(time(0));

    // Configurar o texto 
    fimdejogo.setFont(fonte);
    fimdejogo.setString("Fim de jogo!");
    fimdejogo.setCharacterSize(50);
    fimdejogo.setFillColor(sf::Color::Yellow);
    fimdejogo.setPosition(450, 300); 

    // Configurar o outro texto 
    fimdejogo1.setFont(fonte);
    fimdejogo1.setString("Parabens!");
    fimdejogo1.setCharacterSize(50);
    fimdejogo1.setFillColor(sf::Color::Yellow);
    fimdejogo1.setPosition(450, 300); 
    
    // Configurar o texto "aperte qualquer tecla..."
    inicia1.setFont(fonte);
    inicia1.setString("Aperte qualquer tecla pra iniciar");
    inicia1.setCharacterSize(50);
    inicia1.setFillColor(sf::Color::White);
    inicia1.setPosition(300, 300);

    // Configurar o texto da pontuação
    pontuacao.setFont(fonte);
    pontuacao.setCharacterSize(30);
    pontuacao.setFillColor(sf::Color::Yellow);
    pontuacao.setPosition(540, 0);

    // shape da parede
    sf::RectangleShape rectangle(sf::Vector2f(50, 50));
    rectangle.setFillColor(sf::Color(0, 55, 125));
    sf::CircleShape circle(5);
    circle.setFillColor(sf::Color(255, 255, 0));


    //inicializa a posição do fantasma1
    Fx = 10;
    Fy = 6;

    //inicializa a posição do fantasma2
    Fx2 = 10;
    Fy2 = 6;

    //inicializa a posição do fantasma3
    Fx3 = 10;
    Fy3 = 6;

    //inicializa a posição do fantasma4
    Fx4 = 10;
    Fy4 = 6;

    // sprite do PacMan
    sf::Texture texture;
    if (!texture.loadFromFile("C:/Users/Sousa/Desktop/INF/pacman.png")) {
        std::cout << "Erro lendo imagem pacman.png\n";
        return 0;
    }
    //sprite pra direita
    sf::Sprite spritedir;
    spritedir.setTexture(texture);

    sf::Texture texture2;
    if (!texture2.loadFromFile("C:/Users/Sousa/Desktop/INF/pacman-esq.png")) {
        std::cout << "Erro lendo imagem pacman.png\n";
        return 0;
    }
    //sprite pra esquerda
    sf::Sprite spriteesq;
    spriteesq.setTexture(texture2);

    sf::Texture texture3;
    if (!texture3.loadFromFile("C:/Users/Sousa/Desktop/INF/pacman-cima.png")) {
        std::cout << "Erro lendo imagem pacman.png\n";
        return 0;
    }
    //sprite pra cima
    sf::Sprite spritecima;
    spritecima.setTexture(texture3);

    sf::Texture texture4;
    if (!texture4.loadFromFile("C:/Users/Sousa/Desktop/INF/pacman-baixo.png")) {
        std::cout << "Erro lendo imagem pacman.png\n";
        return 0;
    }
    //sprite pra baixo
    sf::Sprite spritebaixo;
    spritebaixo.setTexture(texture4);

    //sprites dos fantasmas
    sf::Texture texture5;
    if (!texture5.loadFromFile("C:/Users/Sousa/Desktop/INF/fantasmas/fantasma1.png")) {
        std::cout << "Erro lendo imagem fantasma1.png\n";
        return 0;
    }
    sf::Sprite spritefant1;
    spritefant1.setTexture(texture5); //sprite do fantasma 1

    //sprites dos fantasmas
    sf::Texture texture6;
    if (!texture6.loadFromFile("C:/Users/Sousa/Desktop/INF/fantasmas/fantasma2.png")) {
        std::cout << "Erro lendo imagem fantasma2.png\n";
        return 0;
    }
    sf::Sprite spritefant2;
    spritefant2.setTexture(texture6); //sprite do fantasma 2

    //sprites dos fantasmas
    sf::Texture texture7;
    if (!texture7.loadFromFile("C:/Users/Sousa/Desktop/INF/fantasmas/fantasma3.png")) {
        std::cout << "Erro lendo imagem fantasma3.png\n";
        return 0;
    }
    sf::Sprite spritefant3;
    spritefant3.setTexture(texture7); //sprite do fantasma 3

    //sprites dos fantasmas
    sf::Texture texture8;
    if (!texture8.loadFromFile("C:/Users/Sousa/Desktop/INF/fantasmas/fantasma4.png")) {
        std::cout << "Erro lendo imagem fantasma4.png\n";
        return 0;
    }
    sf::Sprite spritefant4;
    spritefant4.setTexture(texture8); //sprite do fantasma 3


    // cria um relogio para medir o tempo
    sf::Clock clock;

    // executa o programa enquanto a janela está aberta
    while (window.isOpen()) {

        // verifica todos os eventos que foram acionados na janela desde a última iteração do loop
        sf::Event event;
        while (window.pollEvent(event)) {
            // evento "fechar" acionado: fecha a janela
            if (event.type == sf::Event::Closed)
                window.close();

            //sequencia de booleanos para verificar se a direção do pacman é válida
            if (event.type == sf::Event::KeyPressed) {     // tecla pressionada
                if (event.key.code == sf::Keyboard::Left) {
                    esq2 = true;
                    dir2 = cima2 = baixo2 = false;
                }
                else if (event.key.code == sf::Keyboard::Right) {
                    dir2 = true;
                    esq2 = cima2 = baixo2 = false;
                }
                else if (event.key.code == sf::Keyboard::Down) {
                    baixo2 = true;
                    esq2 = dir2 = cima2 = false;
                }
                else if (event.key.code == sf::Keyboard::Up) {
                    cima2 = true;
                    esq2 = dir2 = baixo2 = false;
                }
            }
        }
        //condicionais para tentar movimentar o pacman para a direção possível
        if (esq2) {
            if (mapa[posy][posx - 1] != '1') {
                esq = true;   // left key: PacMan passa a mover para esquerda
                dir = cima = baixo = false;
                olhadireita = olhacima = olhabaixo = false;
                olhaesquerda = true;
            }
        }
        else if (dir2) {
            if (mapa[posy][posx + 1] != '1') {
                dir = true;   // right key: PacMan passa a mover para direita
                esq = cima = baixo = false;
                olhaesquerda = olhacima = olhabaixo = false;
                olhadireita = true;
            }
        }
        else if (baixo2) {
            if (mapa[posy + 1][posx] != '1') {
                baixo = true; // down key:PacMan passa a mover para baixo
                esq = dir = cima = false;
                olhadireita = olhacima = olhaesquerda = false;
                olhabaixo = true;
            }
        }
        else if (cima2) {
            if (mapa[posy - 1][posx] != '1') {
                cima = true;  // up key: PacMan passa a mover para cima
                esq = dir = baixo = false;
                olhadireita = olhaesquerda = olhabaixo = false;
                olhacima = true;
            }
        }

        // Muda a posição do PacMan a cada 0.2 segundos
        if (clock.getElapsedTime() > sf::seconds(0.2)) { // tempo desde último restart > 0.2s?
            clock.restart();      // recomeça contagem do tempo
            if (cima)   // muda a posição de acordo com booleano ativo
                if (mapa[posy - 1][posx] != '1')
                    posy--;
            if (baixo)
                if (mapa[posy + 1][posx] != '1')
                    posy++;
            if (esq)
                if (mapa[posy][posx - 1] != '1')
                    posx--;
            if (dir)
                if (mapa[posy][posx + 1] != '1')
                    posx++;

            if (posx > 22)
                posx = 0;
            if (posx < 0)
                posx = 22;
            if (posy > 15)
                posy = 0;
            if (posy < 0)
                posy = 15;

            //movimentação dos fantasmas
            int cont = 0;
            bool caminhocima = false;
            bool caminhobaixo = false;
            bool caminhoesq = false;
            bool caminhodir = false;

            bool caminhos[4] = { caminhocima, caminhobaixo, caminhoesq, caminhodir };  //vetor de booleanos para os possiveis caminhos para o fantasma


            //fantasma1
            if (mapa[Fy - 1][Fx] != '1') {
                caminhocima = true;
                cont++;
            }
            if (mapa[Fy + 1][Fx] != '1') {
                caminhobaixo = true;
                cont++;
            }
            if (mapa[Fy][Fx - 1] != '1') {
                caminhoesq = true;
                cont++;
            }
            if (mapa[Fy][Fx + 1] != '1') {
                caminhodir = true;
                cont++;
            }

            caminhos[0] = caminhocima;
            caminhos[1] = caminhobaixo;
            caminhos[2] = caminhoesq;
            caminhos[3] = caminhodir;

            if (cont > 1) {
                int n;
                do {
                    n = rand() % 4;
                } while (!caminhos[n]);

                if (n == 0 && caminhocima) {
                    Fy--;
                }
                else if (n == 1 && caminhobaixo) {
                    Fy++;
                }
                else if (n == 2 && caminhoesq) {
                    Fx--;
                }
                else if (n == 3 && caminhodir) {
                    Fx++;
                }
            }
            //fantasma2
            cont = 0;  //inicializa o contador de novo
            caminhocima = false;  //coloca falso em tudo de novo
            caminhobaixo = false;
            caminhoesq = false;
            caminhodir = false;

            if (mapa[Fy2 - 1][Fx2] != '1') {
                caminhocima = true;
                cont++;
            }
            if (mapa[Fy2 + 1][Fx2] != '1') {
                caminhobaixo = true;
                cont++;
            }
            if (mapa[Fy2][Fx2 - 1] != '1') {
                caminhoesq = true;
                cont++;
            }
            if (mapa[Fy2][Fx2 + 1] != '1') {
                caminhodir = true;
                cont++;
            }
            if (cont > 1) {
                int n;
                do {
                    n = rand() % 4;
                } while (!caminhos[n]);

                if (n == 0 && caminhocima) {
                    Fy2--;
                }
                else if (n == 1 && caminhobaixo) {
                    Fy2++;
                }
                else if (n == 2 && caminhoesq) {
                    Fx2--;
                }
                else if (n == 3 && caminhodir) {
                    Fx2++;
                }
            }
            //fantasma3 --> esse aqui segue o pacman
            caminhocima = false;  //coloca falso em tudo de novo
            caminhobaixo = false;
            caminhoesq = false;
            caminhodir = false;
            if (mapa[Fy3 - 1][Fx3] != '1') {
                caminhocima = true;
            }
            if (mapa[Fy3 + 1][Fx3] != '1') {
                caminhobaixo = true;
            }
            if (mapa[Fy3][Fx3 - 1] != '1') {
                caminhoesq = true;
            }
            if (mapa[Fy3][Fx3 + 1] != '1') {
                caminhodir = true;
            }
            if (caminhocima && posy < Fy3) {
                Fy3--; // move para cima
            }
            else if (caminhobaixo && posy > Fy3) {
                Fy3++; // move para baixo
            }
            else if (caminhoesq && posx < Fx3) {
                Fx3--; // move para esquerda
            }
            else if (caminhodir && posx > Fx3) {
                Fx3++; // move para direita
            }

            //fantasma4 --> esse aqui segue o pacman
            caminhocima = false;  //coloca falso em tudo de novo
            caminhobaixo = false;
            caminhoesq = false;
            caminhodir = false;

            if (mapa[Fy4 - 1][Fx4] != '1') {
                caminhocima = true;
            }
            if (mapa[Fy4 + 1][Fx4] != '1') {
                caminhobaixo = true;
            }
            if (mapa[Fy4][Fx4 - 1] != '1') {
                caminhoesq = true;
            }
            if (mapa[Fy4][Fx4 + 1] != '1') {
                caminhodir = true;
            }
            if (caminhocima && posy < Fy4) {
                Fy4--; // move para cima
            }
            else if (caminhobaixo && posy > Fy4) {
                Fy4++; // move para baixo
            }
            else if (caminhoesq && posx < Fx4) {
                Fx4--; // move para esquerda
            }
            else if (caminhodir && posx > Fx4) {
                Fx4++; // move para direita
            }
            if (mapa[posy][posx] == '2') {  //remove a pipula do mapa
                mapa[posy][posx] = '0';
                pilula--;
                pontos += 10; //ganha 10 pontos ao encostar em uma pílula
            }
            if (Fx3 == Fx4 && Fy3 == Fy4) {
                Fx3++;
            }
        }
        //atualiza os pontos na tela do jogo
        pontuacao.setString("Pontos: " + std::to_string(pontos));

        if (verifica(posx, posy, Fx, Fy) ||
            verifica(posx, posy, Fx2, Fy2) ||
            verifica(posx, posy, Fx3, Fy3) ||
            verifica(posx, posy, Fx4, Fy4)) {
            perdeu = true;  //agora sim afirma que o jogo acaba porque enconstou em algum fantasma
            clock.getElapsedTime() > sf::seconds(0.0); //congela o tempo
            clock.restart();
        }
        if (pilula == 0) {
            ganha = true;  //jogo acaba pq o fantasma comeu todas as pílulas
            clock.getElapsedTime() > sf::seconds(0.0); //congela o tempo
            clock.restart();
        }

        // limpa a janela com a cor preta
        window.clear(sf::Color::Black);

        // desenhar tudo aqui...

        // desenha paredes
        for (int i = 0; i < 15; i++)
            for (int j = 0; j < 24; j++) {
                if (mapa[i][j] == '1') {
                    rectangle.setPosition(j * 50, i * 50);
                    window.draw(rectangle);
                }
                else if (mapa[i][j] == '2') {
                    circle.setPosition((j * 50) + 25, (i * 50) + 25); //o 25 serve pra centralizar a pílula
                    window.draw(circle);
                }
            }


        // desenha PacMan
        if (olhadireita) {
            spritedir.setPosition(posx * 50, posy * 50);
            window.draw(spritedir);
        }
        else if (olhaesquerda) {
            spriteesq.setPosition(posx * 50, posy * 50);
            window.draw(spriteesq);
        }
        else if (olhacima) {
            spritecima.setPosition(posx * 50, posy * 50);
            window.draw(spritecima);
        }
        else if (olhabaixo) {
            spritebaixo.setPosition(posx * 50, posy * 50);
            window.draw(spritebaixo);
        }


        //desenha fantasmas
        spritefant1.setPosition(Fx * 50, Fy * 50);  //desenha o fantasma 1
        window.draw(spritefant1);

        spritefant2.setPosition(Fx2 * 50, Fy2 * 50);  //desenha o fantasma 2
        window.draw(spritefant2);

        spritefant3.setPosition(Fx3 * 50, Fy3 * 50);  //desnha o fantasma 3
        window.draw(spritefant3);

        spritefant4.setPosition(Fx4 * 50, Fy4 * 50);  //desnha o fantasma 4
        window.draw(spritefant4);

        if (perdeu) {  //se o jogo termina porque perde, "escreve fim de jogo" na tela
            window.draw(fimdejogo);
        }
        if (ganha) {  //se o jogo termina porque ganha, "escreve fim de jogo" na tela
            window.draw(fimdejogo1);
        }
        //desenha pontuação
        window.draw(pontuacao);

        // termina e desenha o frame corrente
        window.display();
    }

    return 0;
}
