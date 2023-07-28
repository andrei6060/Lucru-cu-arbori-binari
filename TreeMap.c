#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "TreeMap.h"

#define MAX(a, b) (((a) >= (b))?(a):(b))


/* Creeaza un arbore cu o serie de metode asociate
 *
 * return: arborele creat
 */
TTree* createTree(void* (*createElement)(void*),
				  void (*destroyElement)(void*),
				  void* (*createInfo)(void*),
				  void (*destroyInfo)(void*),
				  int compare(void*, void*)) {
	TTree* tree=(TTree*)malloc(sizeof(TTree));
	tree->compare=compare;
	tree->createElement=createElement;
	tree->createInfo=createInfo;
	tree->destroyElement=destroyElement;
	tree->destroyInfo=destroyInfo;
	tree->root=malloc(sizeof(TreeNode));
	tree->root=NULL;
	tree->size=0;
	return tree;
}


/* Verifica daca un arbore este gol (vid)
 * 		1 - daca arborele este gol
 * 		0 - in caz contrar
 */
int isEmpty(TTree* tree) {
	if(tree->root==NULL)
	return 1;
	else
	return 0;
}


/* Cauta un anumit element in interiorul unui arbore
 *
 * tree: structura cu metodele asociate arborelui
 *   !folosit pentru a putea compara elementul curent cu cel cautat
 *
 * x: radacina arborelui curent (in care se face cautarea)
 * elem: elementul ce trebuie cautat
 */
TreeNode* search(TTree* tree, TreeNode* x, void* elem) {
	if(x!=NULL)
	{
		if(tree->compare(x->elem, elem)==0)
		return x;
	else if((tree->compare(x->elem, elem)<0)&&(x->right!=NULL))
		return search(tree, x->right,elem);
	if((tree->compare(x->elem, elem)>0)&&(x->left!=NULL))
	return search(tree, x->left,elem);
	return NULL;
	}}


/* Gaseste nodul cu elementul minim dintr-un arbore
 * avand radacina in x
 */
TreeNode* minimum(TreeNode* x) {
	while(x->left!=NULL)
	x=x->left;
	return x;
}

/* Gaseste nodul cu elementul maxim dintr-un arbore
 * avand radacina in x
 */
TreeNode* maximum(TreeNode* x) {
	while(x->right!=NULL)
	x=x->right;
	return x;
}


/* Functie pentru gasirea succesorului unui nod
 * (succesorul in inordine)
 */
TreeNode* successor(TreeNode* x) {
	if(x==NULL) return NULL;
	if(x->right)
		return minimum(x->right);
		
	else{
		TreeNode* aux=x->parent;
		while((aux)&&(x==aux->right)){
		x=aux;
		aux=aux->parent;
		}
		return aux;
		if(maximum(x)==x) return NULL;
	}
}


/* Functie pentru gasirea predecesorului unui nod
 * (predecesorul in inordine)
 */
TreeNode* predecessor(TreeNode* x) {
	if(x==NULL) return NULL;
	if(x->left)
		return maximum(x->left);
		
	else{
		TreeNode* aux=x->parent;
		while((aux)&&(x==aux->left)){
		x=aux;
		aux=aux->parent;
		}
		return aux;
		if(minimum(x)==x) return NULL;
	}
}


/* Actualizeaza inaltimea unui nod din arbore
 */
void updateHeight(TreeNode* x) {

	int leftHeight = 0;
	int rightHeight = 0;

	if (x != NULL) {
		if (x->left != NULL)  leftHeight  = x->left->height;
		if (x->right != NULL) rightHeight = x->right->height;
		x->height = MAX(leftHeight, rightHeight) + 1;
	}
}


/* Functie ce primeste adresa unui arbore si
 * a unui nod x si realizeaza o rotatie la stanga
 * a subarborelui care are varful in x
 *
 *   (x)	 Rotatie    (y)
 *	 / \     stanga     / \
 *  a  (y)    ---->   (x)  c
 *	   / \			  / \
 *    b   c          a   b
 */
void avlRotateLeft(TTree* tree, TreeNode* x) {
	//if (tree == NULL || x == NULL) return;
	TreeNode * y;
	int q=0;
	if(x->parent){
	y=x->parent;
	if((y->left)&&(y->right)){
		if(tree->compare(y->left->elem,x->elem)==0){
			q=1;
		}
		else
		q=2;
		}
	else if(y->right)
		q=2;
	else 
		q=1;
		}
	TreeNode* z=x->right;
	x->right=z->left;
	z->left=x;
	x->parent=z;
	updateHeight(x);
	updateHeight(z);
	if(q==1){
		{y->left=z;
		z->parent=y;}
	}
	else if(q==2)
		{y->right=z;
		z->parent=y;}
	else {tree->root=z;
			tree->root->parent=NULL;
	}
}


/* Functie ce primeste adresa unui arbore si
 * a unui nod x si realizeaza o rotatie la dreapta
 * a subarborelui care are varful in y
 *
 *     (y)	 Rotatie    (x)
 *	   / \   dreapta    / \
 *   (x)  c   ---->    a  (y)
 *	 / \			      / \
 *  a   b                b   c
 */
void avlRotateRight(TTree* tree, TreeNode* y) {
	

	TreeNode * x;
	int q=0;
	if(y->parent){
	x=y->parent;
	if((x->left)&&(x->right)){
		if(tree->compare(x->left->elem,y->elem)==0){
			q=1;
		}
		else
		q=2;
		}
	else if(x->right)
		q=2;
	else 
		q=1;
		}
	printf("\n\nATAT ESTE Q!!!!!!%d\n\n",q);
	TreeNode* z=y->left;
	y->left=z->right;
	z->right=y;
	y->parent=z;
	updateHeight(y);
	updateHeight(z);
	if(q==1)
		{x->left=z;
		z->parent=x;}
	else if(q==2)
		{x->right=z;
		z->parent=x;}
	else{
	tree->root=z;
	tree->root->parent=NULL;
	}
	
}


/* Calculeaza factorul de echilibrare pentru un nod x
 * (AVL balance factor)
*/
int avlGetBalance(TreeNode *x) {
	if(x==NULL)
	return 0;
	if((x->left==NULL)&&(x->right!=NULL)){
		return 0-x->right->height;
	}
	else if((x->left!=NULL)&&(x->right==NULL)){
		return x->left->height;
	}
	else if((x->left==NULL)&&(x->right==NULL)){
		return 0;
	}
	else 
	return x->left->height-x->right->height;
}


/* Functie pentru reechilibrarea unui arbore AVL
 * in urma unei inserari prin rotatii simple sau duble
 * si recalcularea inaltimii fiecarui nod intalnit parcurgand
 * arborele de jos in sus, spre radacina
 *
 */
void avlFixUp(TTree* tree, TreeNode* y) {
	TreeNode* curr=y;
	while(curr->parent!=NULL){
		updateHeight(curr->parent);
		curr=curr->parent;
	}
	// curr=y;
	// while(curr->parent!=NULL){
	// 	int nr=avlGetBalance(curr);
	// 	if(nr>1)
	// 		avlRotateRight(tree,curr);
	// 	else if(nr<-1)
	// 		avlRotateLeft(tree,curr);	
	// }
	int bf;
	TreeNode* pp;
	if((y->parent)&&(y->parent->parent))
			{
				pp=y->parent->parent;
				if(pp->left==NULL)
					bf=0-pp->right->height;
				else if(pp->right==NULL)
					bf=pp->left->height;
				else
					bf=pp->left->height-pp->right->height;
			}
	else{
	if(tree->root->left==NULL)
		bf=0-tree->root->right->height;
	else if(tree->root->right==NULL)
		bf=tree->root->left->height;
	else
		bf=tree->root->left->height-tree->root->right->height;
	}//printf("bf: %d\n",bf);
	if((bf<-1)&&(tree->compare(y->elem,tree->root->right->elem)==1))
	avlRotateLeft(tree,y->parent->parent);
	 if((bf>1)&&(tree->compare(y->elem,tree->root->left->elem)==-1))
	 	avlRotateRight(tree,y->parent->parent);

}


/* Functie pentru crearea unui nod
 *
 * value: valoarea/cheia din cadrul arborelui
 * info: informatia/valoarea din dictionar
 */
TreeNode* createTreeNode(TTree *tree, void* value, void* info) {

	if (tree == NULL) 
		return NULL;

	// Alocarea memoriei
	TreeNode* node = (TreeNode*) malloc(sizeof(TreeNode));

	// Setarea elementului si a informatiei
	node->elem = tree->createElement(value);
	node->info = tree->createInfo(info);

	// Initializarea legaturilor din cadrul arborelui
	node->parent = node->right = node->left = NULL;

	// Initializarea legaturilor din cadrul listei dublu inlantuite
	node->next = node->prev = node->end = NULL;


	// Inaltimea unui nod nou este 1
	// Inaltimea lui NULL este 0
	node->height = 1;

	return node;
}


/* Inserarea unul nou nod in cadrul multi-dictionarului
 * ! In urma adaugarii arborele trebuie sa fie echilibrat
 *
 */
void insert(TTree* tree, void* elem, void* info) {
	// //printf("%ld\n",tree->createInfo(info));
	TreeNode* new_node=createTreeNode(tree,elem,info);
	 if(isEmpty(tree)){
		tree->root=new_node;
		tree->root->end=tree->root;
		tree->size=1;
		printf("gogu\n");
	 }
	 
	else if(search(tree,tree->root,elem)!=NULL){
		 
		 //printf("plt\n");
		 
		 //printf("%ld %ld\n\n", *((long*)(new_node->elem)), *((long*)(new_node->info)));
	 }
	 else {
		 printf("plm\n");
		 //printf("%ld %ld\n\n", *((long*)(new_node->elem)), *((long*)(new_node->info)));
		 TreeNode* curr=tree->root;
		int placed=0;
		while(!(placed)){
			if(tree->compare(new_node->elem,curr->elem)<0){
				if(curr->left==NULL){
					if(curr->parent->right==curr){
						tree->size=tree->size+1;
					
					new_node->parent=curr;
					new_node->end=new_node;
					curr->right=new_node;
					void* aux=curr->elem;
					void* auxx=curr->info;
					curr->elem=new_node->elem;
					curr->info=new_node->info;
					new_node->elem=aux;
					new_node->info=auxx;

					new_node->next=successor(new_node);
					if(new_node->next!=NULL)
						new_node->next->prev=new_node;
					new_node->prev=predecessor(new_node);
					if(new_node->prev!=NULL)
						new_node->prev->next=new_node;

					// printf("curr left--%ld\n", *((long*)curr->left->parent->elem));
					avlFixUp(tree,curr->right);
					//printf("intrus--%ld\n", *((long*)new_node->elem));	
					}
					
					else{
					tree->size=tree->size+1;
					new_node->parent=curr;
					new_node->end=new_node;
					curr->left=new_node;
					new_node->next=successor(new_node);
					if(new_node->next!=NULL)
						new_node->next->prev=new_node;
					new_node->prev=predecessor(new_node);
					if(new_node->prev!=NULL)
						new_node->prev->next=new_node;
					printf("curr left--%ld\n", *((long*)curr->left->parent->elem));
					avlFixUp(tree,curr->left);}
					placed=1;
					
				}
				else{
					curr=curr->left;
				}
			}
			else{
				if(curr->right==NULL){
					tree->size=tree->size+1;
					new_node->parent=curr;
					new_node->end=new_node;
					curr->right=new_node;
					placed=1;
					new_node->next=successor(new_node);
					if(new_node->next!=NULL)
						new_node->next->prev=new_node;
					new_node->prev=predecessor(new_node);
					if(new_node->prev!=NULL)
						new_node->prev->next=new_node;
					avlFixUp(tree,curr->right);
					
					
				}
				else{
					curr=curr->right;
				}
			}
		}
	 }
	 
}


/* Eliminarea unui nod dintr-un arbore
 *
 * ! tree trebuie folosit pentru eliberarea
 *   campurilor `elem` si `info`
 * */
void destroyTreeNode(TTree *tree, TreeNode* node){

	// Verificarea argumentelor functiei
	if(tree == NULL || node == NULL) return;

	// Folosirea metodelor arborelui
	// pentru de-alocarea campurilor nodului
	tree->destroyElement(node->elem);
	tree->destroyInfo(node->info);

	// Eliberarea memoriei nodului
	free(node);
}


/* Eliminarea unui nod din arbore
 *
 * elem: cheia nodului ce trebuie sters
 * 	! In cazul in care exista chei duplicate
 *	  se va sterge ultimul nod din lista de duplicate
 */
void delete(TTree* tree, void* elem) {
	if(isEmpty(tree)){
		return;
	}
	else{
		TreeNode * de_elim=search(tree,tree->root,elem);
		//printf("%ld\n", *((long*)de_elim->next->elem));
		//printf("%ld\n\n", *((long*)de_elim->prev->elem));
		if(tree->root!=de_elim){
			if((de_elim->left==NULL)&&(de_elim->right==NULL)){
				printf("%ld\n",*((long*)de_elim->elem));
				if(de_elim->next)
					de_elim->next->prev=de_elim->prev;
				if(de_elim->prev)
				de_elim->prev->next=de_elim->next;
				
				TreeNode * p=de_elim->parent;
				if(p->left==de_elim){
					destroyTreeNode(tree,de_elim);
					p->left=NULL;
				}
				else if(p->right=de_elim){
					destroyTreeNode(tree,de_elim);
					p->right=NULL;
				}
					if(avlGetBalance(p)<-1){
						if(p->right->left!=NULL){
							printf("smbt mami\n");
							TreeNode* ci=p->right;
							TreeNode* doi=p->right->left;
							printf("?????????????????\n");
							printf("%ld\n",*((long*)ci->elem));
							printf("%ld\n\n",*((long*)ci->prev->elem));
							//printf("%ld\n\n",*((long*)(*tree)->root->next->elem));

							printf("%ld\n",*((long*)doi->elem));
							printf("%ld\n",*((long*)doi->next->elem));
							printf("%ld\n\n",*((long*)doi->prev->elem));
							printf("?????????????????\n");
							//printf("%ld\n",*((long*)(*tree)->root->left->elem));
							//printf("%ld\n\n",*((long*)(*tree)->root->left->next->elem));
							void* aux=ci->next;
							void* auxx=ci->prev;
							ci->next=doi->next;
							ci->prev=doi->prev;
							doi->next=aux;
							doi->prev=auxx;

							aux=ci->elem;
							auxx=ci->info;
							ci->elem=doi->elem;
							ci->info=doi->info;
							doi->elem=aux;
							doi->info=auxx;
							
							

							ci->right=doi;
							ci->left=NULL;
							avlRotateLeft(tree,p);
							// doi->next=successor(doi);
							// if(doi->next!=NULL)
							// 	doi->next->prev=doi;
							// doi->prev=predecessor(new_node);
							// if(doi->prev!=NULL)
							// 	doi->prev->next=new_node;
						}
						else
							avlRotateLeft(tree,p);
					}
					else if(avlGetBalance(p)>1){
						avlRotateRight(tree,p);
					}
				
			}
			// else if((de_elim->left!=NULL)&&(de_elim->right==NULL)){

			// }
			else if((de_elim->left==NULL)&&(de_elim->right!=NULL)){
				de_elim->prev->next=de_elim->next;
				de_elim->next->prev=de_elim->prev;
				TreeNode * p=de_elim->parent;
				TreeNode* q=de_elim->right;
				// printf("%ld\n",*((long*)p->right->elem));
				// printf("%ld\n",*((long*)p->elem));
				// printf("%ld\n",*((long*)p->right->right->elem));
				p->right=q;
					printf("jomama\n");
					q->parent=p;
				destroyTreeNode(tree,de_elim);
				// printf("%ld\n",*((long*)tree->root->elem));
				// printf("%ld\n",*((long*)tree->root->next->elem));
				// printf("%ld\n",*((long*)tree->root->prev->elem));
				// printf("%ld\n",*((long*)tree->root->right->prev->elem));
				
			}
			// else{

			// }
		}
		else{
			if((de_elim->left==NULL)&&(de_elim->right==NULL)){
				printf("nu mai pot\n");
				tree->size=0;
				destroyTreeNode(tree,de_elim);
				tree->root=NULL;
			}
			else if((de_elim->left->right==NULL)&&(de_elim->left->left==NULL)&&(de_elim->right->left==NULL)&&(de_elim->right->right==NULL)){
				// printf("cf rasvan\n");
				// tree->root=NULL;
				// tree->size=0;
				tree->root=tree->root->right;
				tree->root->left=de_elim->left;
				tree->root->next=NULL;
				tree->root->parent=NULL;
				tree->root->left->parent=tree->root;
				tree->root->prev=tree->root->left;
				tree->root->left->next=tree->root;
				destroyTreeNode(tree,de_elim);
			}
			else{
			tree->size--;
			TreeNode * succ=successor(de_elim);
			


			void* plm=succ->elem;
			void* plt=succ->info;
			succ->elem=de_elim->elem;
			succ->info=de_elim->info;
			de_elim->elem=plm;
			de_elim->info=plt;   
			
			

			TreeNode* auxxx=de_elim->prev;
			de_elim->prev=succ->prev;
			succ->prev=auxxx;

			auxxx=de_elim->next;
			de_elim->next=succ->next;
			succ->next=auxxx;

			auxxx=de_elim->end;
			de_elim->end=succ->end;
			succ->end=auxxx;
			tree->root=de_elim;
			
			TreeNode * pa=succ->parent;
			succ->prev->next=succ->next;
			succ->next->prev=succ->prev;
			succ->next=tree->root;
			tree->root->prev=succ->prev;
			if((pa->left==succ)&&(succ->left==NULL)&&(succ->right==NULL)){
			 	destroyTreeNode(tree,succ);
				pa->left=NULL;
			 }
			tree->root->parent=NULL;
			tree->root->right->prev=tree->root;
			 tree->root->left->right->next=tree->root;}

		}
	}
	}



/* Eliberarea memoriei unui arbore
 */
void destroyTree(TTree* tree){

	/* Se poate folosi lista dublu intalntuita
	 * pentru eliberarea memoriei
	 */
	if (tree == NULL || tree->root == NULL)
		return;
}