#include<iostream>
struct List
{
	int data;
	List * next;
};
int main()
{
	void init(List &L);
	void rev(List &L);
	void buildL(List &L);
	List head;
	init(head);
	List * p;

	buildL(head);
		p=head.next;
		rev(head);

return 0;
}

void init(List &L)
{
//	L =new List;
	L.next = NULL;
}
void buildL(List &L)
{
	int i;
	List *p,*cur;
	cur = &L;
	for(i=0;i<20;i++)
	{
		p = new List;
		p->next = NULL;
		p->data = i;
		cur->next = p;
		cur = p;
	}

}
void rev(List &L)
{
	List * p;
	List * q;
	List * s;
	List * head;
	head = &L;
	p=head->next;
	q=p->next;
	p->next = NULL;

	while(q!=NULL)
	{
		s=q->next;
		p=head->next;
		head->next = q;
		q->next = p;
		q=s;
	}
	p=L.next;
	while(p!=NULL)
	{
		printf("%d ",p->data);
		p=p->next;
	}

}
