#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<string>::iterator prvni(vector<string> &v, const char *filter)
{
    for (auto it = v.begin(); it != v.end(); it++)
    {
        if ((*it).find(filter) != string::npos)
        {
            return it;
        }
    }
    return v.end();
}

vector<string>::iterator dalsi(vector<string> &v, vector<string>::iterator it_lfname, const char *filter)
{
    it_lfname++;
    while (it_lfname != v.end())
    {
        if ((*it_lfname).find(filter) != string::npos)
        {
            return it_lfname; // break
        }
        it_lfname++;
    }
    return it_lfname;
}

int main(int argc, char const *argv[])
{
    const char *Jmena[] =
        {"Marie", "Jan", "Jana", "Petr", "Josef", "Pavel", "Jaroslav", "Martin", "Miroslav", "Eva",
         "Anna", "Hana", "Karel", "Lenka", "Milan", "Michal", "Alena", "Petra", "Lucie", "Jaroslava",
         "Ludmila", "Helena", "David", "Ladislav", "Marie", "Jan", "Jana", "Petr", "Jitka", "Martina", "Jakub", "Veronika", "Jarmila", "Stanislav",
         "Michaela", "Ivana", "Roman", "Jarmila", "Monika", "Tereza", "Zuzana", "Radek", "Vlasta", "Marcela", "Marek",
         "Dagmar", "Dana", "Daniel", "Marta", "Irena", "Monika", "Miroslava", "Barbora", "Ilona", "Pavla", "Miloslav", "Olga",
         "Andrea", "Iveta", "Hana", "Filip", "Ilona", "Blanka", "Milada", "Ivan", "Zdenka", "Libor", "Renata", "Rudolf",
         "Vlastimil", "Nikola", "Gabriela", "Lenka", "Adam", "Lenka", "Milan", "Radka", "Simona", "Milena", "Miloslava", "Iva", "Daniela",
         "Patrik", "Bohumil", "Denisa", "Robert", "Diana", "Romana", "Aneta", "Ilona", "Dominik", "Jakub", "Stanislava", "Emilie",
         "Radim", "Richard", "Kamila", "Ivo", "Monika", "Rostislav", "Vladislav", "Bohuslav", "Alois", "Vit", "Kamil",
         "Jozef", "Vendula", "Bohumila", "Viktor", "Emil", "Michael", "Ladislava", "Diana", "Magdalena", "Eduard", "Dominika",
         "Marcel", "Adam", "Sabina", "Julie", "David", "Johana", "Antonie", "Josef", "Alice", "Peter", "Dalibor", "Kristina", "Otakar", "Karla",
         "Hedvika", "Alexandra", "Silvie", "Erika", "Nela", "Irena", "Vratislav", "Nikol", "Leona", "Jolana", "Margita",
         "Bohuslava", "Radovan", "Jan", "Jana", "Josefa", "Terezie", "Marian", "Linda", "Igor", "Jarmila", "Magda", "Lada", "Bohumir",
         "Alexandr", "Radim", "Adriana", "Dita", "Hana", "Vladislava", "Otto", "Sandra", "Radmila", "Svatava", "Darina", "Sylva",
         "Viktorie", "Ivona", "David", "Monika", "Jarmila", "Lenka", "Bronislava", "Elena", "Svatopluk", "Ivanka", "Denis", "Adolf", "Hynek", "Erik",
         "Bronislav", "Jakub", "Drahoslava", "Petr", "Alexander", "Robin", "Maria", "Diana", "Lidmila", "Vlastislav", "Michala", "Jindra",
         "Juraj", "Vlastimila", "Karin", "Zdena", "Jan", "Josef", "Jana", "Karolina", "Mykola", "Pavol", "Vanda", "Radoslav", "Zdenek",
         "Alenka", "Ema", "Andrej", "Tibor", "Anton", "Ingrid", "Nina", "Irena", "Viera", "Linda", "Valerie", "Samuel",
         "Zlata", "Lydie", "Tamara", "Johana", "Jan", "Jana", "Patricie", "Julius", "Boris", "Leopold", "Ota", "Ester",
         "Gertruda", "Sylvie", "Aloisie", "Oto", "Barbara", "Gustav", "Marika", "Yvona", "Jitka", "Oksana", "Bohdan"};

    vector<string> v_names;
    v_names.reserve(50);
    
    for (auto name:Jmena)
    {
        v_names.push_back(name);
    }

    string filter;
    cout << "Filtr: ";
    cin >> filter;
    
    int names_printed = 0;
    for(auto it = prvni(v_names, filter.c_str()); it != v_names.end(); it = dalsi(v_names, it, filter.c_str())){
        cout << *it;
        names_printed++;
        if(names_printed == 10){
            cout << endl;
            names_printed = 0;
        }
        else{
            cout << " ";
        }
    }

    return 0;
}
