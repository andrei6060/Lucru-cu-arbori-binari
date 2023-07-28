Tema 2 - SDA

createTree - aloca memorie pentru un arbore
		- initializeaza fiecare camp, si functiile din antet
		- seteaza root la NULL si size la 0
		- returneaza arborele creeat
isEmpty - verifica daca arborele este gol
	- daca tree->root este NULL sau tree->size = 0 , atunci arborele
	este vid si se returneaza 1
	- daca arborele este nevid, atunci se returneaza 0
search - cauta daca un element exista in arbore, iar in caz contrar
		 returneaza null
	-se foloseste functia compare, care returneaza un numar <0, daca
		elementul din dreapta e mai mare, un numar >0 daca cel din stanga
		e mai mare, si 0 daca cele 2 elemente sunt egale
minimum - returneaza nodul cel mai din stanga pornind de la nodul dat ca
		parametru
maximum- returneaza nodul cel mai din dreapta pornind de la nodul dat ca
		parametru
successor- returneaza minimul din subarborele drept al nodului dat ca
		parametru, in caz ca subarborele drept exista
		-in caz contrar cauta in stramosii nodului, pana cand parintele e null
predecessor- returneaza maximul din subarborele stang al nodului dat ca
		parametru, in caz ca subarborele stang exista
		-in caz contrar cauta in stramosii nodului, pana cand parintele e null
avlRotateLeft - rotestele arborele ce pleaca de la nodul dat ca parametru
			la stang
			- pastreaza legaturile dintre noduri
			- updateaza inaltimile nodurilor
avlRotateRight - rotestele arborele ce pleaca de la nodul dat ca parametru
			la dreapta			
			- pastreaza legaturile dintre noduri
			- updateaza inaltimile nodurilor
avlFixUp- balanseaza arborele plecand de la nodul transmis ca parametru

insert-insereaza un nod in arbore, creeaza legaturile specifice, atat
	atat pentru arbore cat si pentru lista

delete-sterge un nod din arbore, rupe legaturile specifice, atat
	atat pentru arbore cat si pentru lista