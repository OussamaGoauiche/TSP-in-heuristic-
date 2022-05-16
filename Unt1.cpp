#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;
class TSP
{
private:
int num_cities; // number of cities
int ** distances; // distances matrix
public:
TSP(char*); // constructor from an input file
int get_num_cities() ;
void print();
int get_dist(int, int);
// compute the distance between ci and cj
int * Nearest_Neighbor(int *);
// The heuristic
};
//Constructeur de ce classe
TSP::TSP(char* filename){
int number,i,j;
//ouvrir une flux
ifstream input_file(filename);
//lecture du nombre de villes
input_file >> number;
//initialise l'attribue num_cities
num_cities=number;
//remplissage d'une matrice triangulaire nbr_ligne=num_cities-1 
distances=new int* [num_cities];
cout<<num_cities<<endl;
for(i=0;i<num_cities;i++){
distances[i]=new int[num_cities-i];
for(j=0;j<num_cities-i-1;j++){
input_file >> number;
*(distances[i]+j)=number;
}
}
input_file.close();
}
//Fin de d?finition
//retourn le nombre de villes
int TSP::get_num_cities(){
return num_cities;
}
//Affichage du matrice des distances 
void TSP::print(){
int i,j,k;
cout<<"Number of cities : "<<get_num_cities()<<endl;
cout<<"Matrix of distances between cities"<<endl;
for(i=0;i<get_num_cities();i++){
for(k=0;k<i;k++){
cout<<*(distances[k]+i-k-1)<<"\t"; 
}
cout<<0<<" "; 
for(j=0;j<get_num_cities()-i-1;j++){
cout<<*(distances[i]+j)<<"\t";
}
cout<<endl;
}
}
//Fin de d?finition
//distances entre de villes m et n
int TSP::get_dist(int n,int m){
if(n==m)
return 0;
else if(n<m)
return distances[n][m-n-1];
else
return distances[m][n-m-1];
}
//fin
//Voisin le plus proche
int *TSP::Nearest_Neighbor(int *co){
//tableau du sortie
int *result=new int[num_cities+1];
//tableau des villes non parcourir (tout ville parcouri sa case contient -1)
int *rest=new int[num_cities-1];
//Le nombre de villes d?ja on le traites
int p=0;
//ville actualle
int c;
//Ville ? ?liminer
int s;
//simple compteurs
int i,j;
//Cout minimum
int min;
//intialisation du cout
*co=0;
cout<<"Choose a departure city : ";
cin>>c;
*(result+p)=c;
//remplissage du table du reste
for(i=0;i<num_cities;i++){
if(i!=c)
{
//pr?paration du valeur initiale min
min=get_dist(c,i);
//rien
*(rest+i)=1;
}
else
*(rest+i)=-1;
}
while(p<num_cities-1){
//trouv? cout minimum du ville actuelle c par rapport au villes existants dans tab rest
for(i=0;i<num_cities;i++){
//test si la ville est rest?
if(rest[i]!=-1){
//une distance plus petit
if(get_dist(c,i)<=min){
//m?moris?e le cout minimum et num de ville ? retir?
min=get_dist(c,i);
s=i;
}
}
}
*co+=min;
rest[s]=-1;
c=s;
p++;
*(result+p)=s;
for(j=0;j<num_cities;j++){
if(rest[j]!=-1)
min=get_dist(c,j);
}
}
//insetion de la dernier ville 
for(i=0;i<num_cities;i++){
if(rest[i]!=-1){
*co+=get_dist(c,i); 
*(result+num_cities-1)=i;
*(rest+i)=-1;
c=i;
break;
}
}
*(result+num_cities)=*result;
*co+=get_dist(c,result[0]); 
//result :)
return result;
}
//fin
/*---------------------------------------APPLICATION-------------------------------
-------------------------------------
-----------------------------------------APPLICATION-------------------------------
-------------------------------------
-----------------------------------------APPLICATION-------------------------------
-----------------------------------*/
int main(){
int i;
char c;
string f;
char*filename;
cout<<"Enter the input file name : ";
cin>>f;
filename=(char*)f.c_str();
TSP test(filename);
test.print();
int* co=(int*)malloc(sizeof(int));
int *result=new int[test.get_num_cities()+1];
while(1){
result=test.Nearest_Neighbor(co);
for(i=0;i<=test.get_num_cities();i++){
cout<<*(result+i);
if(i<test.get_num_cities())
cout<<"-->";
}
cout<<" "<<endl;
cout<<"It's cost is : "<<*co<<endl;
cout<<" "<<endl; 
cout<<"Continue ?? y or n"<<endl;
cin>>c;
if(c=='n')
break;
}
return 0;
}
