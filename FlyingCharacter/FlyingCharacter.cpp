// FlyingCharacter.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//
#include <windows.h>
#include "NYTimer.h"
#include "Player.h"
#include "GameManager.h"
#include <iostream>

LONG_PTR setConsoleWindowStyle(INT n_index, LONG_PTR new_style)
{
    /*The function does not clear the last error information. if last value was zero.*/
    SetLastError(NO_ERROR);

    HWND hwnd_console = GetConsoleWindow();
    LONG_PTR style_ptr = SetWindowLongPtr(hwnd_console, n_index, new_style);
    SetWindowPos(hwnd_console, 0, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_DRAWFRAME);

    //show window after updating
    ShowWindow(hwnd_console, SW_SHOW);

    return style_ptr;
}

int main()
{
    GameManager gm;
    gm.init();
    Player player(50,10);
    Vec2<int> velocity;
    while (1){
        //Input
        velocity = player.GetInput();

        if (gm.clock.getElapsedSeconds(false) > FRAMERATE)
        {
            player.Move(velocity);
            //Reset timer
            gm.clock.Reset();

            //Flush buffer
            gm.Flush();
            //write buffer
            if (player.facingLeft)
            {
                for (int i = 0; i < player.sizeX; i++)
                {
                    for (int j = 0; j < player.sizeY; j++)
                    {
                        gm.buffer[player.posY + j][player.posX + i].Char.AsciiChar = player.idleLeft[player.frame][i + player.sizeX * j];
                        gm.buffer[player.posY + j][player.posX + i].Attributes = player.color;
                    }
                }
            }
            else
            {
                for (int i = 0; i < player.sizeX; i++)
                {
                    for (int j = 0; j < player.sizeY; j++)
                    {
                        gm.buffer[player.posY + j][player.posX + i].Char.AsciiChar = player.idleRight[player.frame][i + player.sizeX * j];
                        gm.buffer[player.posY + j][player.posX + i].Attributes = player.color;
                    }
                }
            }

            
            player.ChangeFrame();

            //write screen
            gm.WriteToConsole();
        }
    }  
    return 0;
}


// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.


/*

    Décor
    DrawDecor ( ListDecor)
    Plateforme

    Ennemi/projectile

    Joueur

    Decor.Coord
    Decor.Image

    Player.Image


    Affichage
    Collision
    Génération de niveau

    Dessiner joueur
    déplacer joueur                                                        
    collision plateforme

    score = hauteur + projectiles détruits + collectible...

    saut = 5 ligne

    une plateforme toutes les 3 lignes
    1 ennemi toutes les 2 plateformes
    un projectile toutes les 1,5 plateformes


    Input
    Physics
        Position
        Collision
            Damage
                Arrière mort
                Avant -1 vie et 3 secondes invulnérabilité
    Draw
*/