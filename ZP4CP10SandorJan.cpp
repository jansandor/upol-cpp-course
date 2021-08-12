#include <iostream>
#include <string>

using namespace std;

int main(int argc, char const *argv[])
{
  string Jmena("MarieJanJanaPetrJosefPavelJaroslavMartinMiroslavEva"
               "AnnaHanaKarelLenkaMilanMichalAlenaPetraLucieJaroslava"
               "LudmilaHelenaDavidLadislavJitkaMartinaJakubVeronikaJarmilaStanislav"
               "MichaelaIvanaRomanMonikaTerezaZuzanaRadekVlastaMarcelaMarek"
               "DagmarDanaDanielMartaIrenaMiroslavaBarboraPavlaMiloslavOlga"
               "AndreaIvetaFilipBlankaMiladaIvanZdenkaLiborRenataRudolf"
               "VlastimilNikolaGabrielaAdamRadkaSimonaMilenaMiloslavaIvaDaniela"
               "PatrikBohumilDenisaRobertRomanaAnetaIlonaDominikStanislavaEmilie"
               "RadimRichardKamilaIvoRostislavVladislavBohuslavAloisVitKamil"
               "JozefVendulaBohumilaViktorEmilMichaelLadislavaMagdalenaEduardDominika"
               "MarcelSabinaJulieAntonieAlicePeterDaliborKristinaOtakarKarla"
               "HedvikaAlexandraSilvieErikaNelaVratislavNikolLeonaJolanaMargita"
               "BohuslavaRadovanJosefaTerezieMarianLindaIgor");
    int row_len;
    cout << "Delka radku: ";
    cin >> row_len;    
    for(int last_space_index = 0, i = 1, chars_on_row = 1; i < Jmena.length(); i++){
        if(isupper(Jmena[i])){
            Jmena.insert(i, 1, ' ');
            last_space_index = i;
            i++;
            chars_on_row++;
        }
        if(chars_on_row >= row_len){
            Jmena.replace(last_space_index, 1, "\n");
            chars_on_row = i - last_space_index;
            continue;
        }
        chars_on_row++;
    }
    cout << Jmena << endl;

    return 0;
}