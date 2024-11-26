#include <vector>
#include <string>

using namespace std;
using Plateau = vector<vector<int>>;

class Jeu {
    public:
        Plateau plateau;
        int score;

        /**
         * Ajoute un quatre ou un deux de manière aléatoire à la place d'un zero sur le plateau
         **/

        void ajouterDeuxOuQuatre();

        /**
         * Echange les lignes et les colonnes du plateau
         **/

        void echangerLignesEtColonnes();

        /** 
         * Fusionne et aligne (vers la droite ou la gauche) les éléments des lignes du plateau en mettant à jour le score
         * @param droite qui specifie s'il faut aligner a droite 
         **/

        void fusionnerEtAlignerLesLignes(bool droite);
        

        /** deplace les tuiles du plateau dans la direction donnée
         * @param direction la direction
         * @return true s'il y a eu un deplacement, false sinon
         **/

        bool deplacement(string direction);

        /** permet de savoir si une partie est terminée
         *  @return true si le plateau est vide, false sinon
         **/
        bool estTermine();

        /** creer le dessin du plateau
         * @return le dessin du plateau en string
         **/

        string obtenirDessin();

        Jeu();
        
        Jeu(const Jeu& autre) {
            this->plateau = autre.plateau;  // Copie du plateau
            this->score = autre.score;      // Copie du score
        }
};

/** génère aléatoirement un 2 ou un 4 avec des probabilités respectives de 9/10 et 1/10
 *  @return 2 ou 4
 **/
int tireDeuxOuQuatre();

/** 
 * retourne une ligne du tableau
 * @param ligne un tableau a 4 entiers
 * @return la ligne retournee
 **/

vector<int> retournerLigne(vector<int> ligne);

/** 
 * Cherche la taille du nombre le plus long du tableau
 * @param plateau le plateau
 * @return la taille du nombre le plus long du tableau
 **/

int tailleDuNombreLePlusLong(Plateau plateau);