#include<stdios>
#include<>
struct List
{
	int data;
	List * next;
};
int main()
{
	void init(List *L);
	List * head;
	init(head);


}
void init(List *L)
{
	int i;
	List * head,p,q;
	head = L;
	p=L->next;
	for(i=0;i<20;i++)
	{
		p->data = i;
		

	}
}