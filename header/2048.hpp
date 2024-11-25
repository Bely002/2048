#include <vector>

using namespace std;
using Plateau = vector<vector<int>>;

class Jeu {
    public:
        Plateau plateau;
        int score;

        void initialiser();
        void ajouterDeuxOuQuatre();
}

/** génère aléatoirement un 2 ou un 4 avec des probabilités respectives de 9/10 et 1/10
 *  @return 2 ou 4
 **/
int tireDeuxOuQuatre();

/** génère un plateau de dimensions 4*4 ne contenant que des 0
 *  @return un plateau vide
 **/
Plateau plateauVide();

/**
 * Ajoute un quatre ou un deux à la place d'un zero
 * @param plateau le plateau
 * @return le plateau avec un quatre ou un deux à la place d'un ancien zero
 **/
Plateau ajouterDeuxOuQuatre(Plateau plateau);

/**
 * Echange les lignes et les colonnes du plateau
 * @param plateau le plateau
 * @return le plateau avec les lignes et les colonnes echangees 
 **/

Plateau echangerLignesEtColonnes(Plateau plateau);

/** 
 * retourne une ligne du tableau
 * @param ligne un tableau a 4 entiers
 * @return la ligne retournee
 **/

vector<int> retournerLigne(vector<int> ligne);

/** 
 * Fusionne et aligne (vers la droite ou la gauche) les éléments des lignes du plateau
 * @param jeu le jeu avec le plateau et le score
 * @param droite qui specifie s'il faut aligner a droite
 * @return le jeu avec le plateau et le score actualises
 **/

Jeu fusionnerEtAlignerLesLignes(Jeu jeu,bool droite);


/** déplace les tuiles d'un plateau dans la direction donnée et génère une nouvelle tuile si le déplacement est valide
 *  @param Jeu le jeu avec le plateau
 *  @param direction la direction
 *  @return le jeu avec le plateau déplacé dans la direction indiqué et le score mis à jour
 **/
Jeu deplacement(Jeu jeu, int direction);

/** 
 * cherche la taille du nombre le plus long dans le plateau
 * @param plateau le plateau
 * @return la taille du nombre le plus long
 **/
int tailleDuNombreLePlusLong(Plateau plateau);

/** affiche un plateau
 * @param p le plateau
 * @return le string correspondant à l'affichage du tableau
 **/
string dessine(Plateau p);

/** permet de savoir si une partie est terminée
 *  @param plateau un plateau
 *  @return true si le plateau est vide, false sinon
 **/
bool estTermine(Plateau plateau);
 

/** permet de savoir si une partie est gagnée
 * @param plateau un plateau
 * @return true si le plateau contient un 2048, false sinon
 **/

bool estGagnant(Plateau plateau);