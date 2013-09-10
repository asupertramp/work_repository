 /* bo5-52.c ���������д��ʽ��ΪHString���� */
 #include"c4-2.h" /* ����HString���� */
 #include"bo4-2.c" /* HString���͵Ļ������� */
 Status sever(HString *str,HString *hstr)
 { /* ���ǿմ�str�ָ��������:hstrΪ��һ��','֮ǰ���Ӵ�,strΪ֮����Ӵ� */
   int n,i=1,k=0; /* k����δ��Ե������Ÿ��� */
   HString ch,c1,c2,c3;
   InitString(&ch); /* ��ʼ��HString���͵ı��� */
   InitString(&c1);
   InitString(&c2);
   InitString(&c3);
   StrAssign(&c1,",");
   StrAssign(&c2,"(");
   StrAssign(&c3,")");
   n=StrLength(*str);
   do
   {
     SubString(&ch,*str,i,1);
     if(!StrCompare(ch,c2))
       ++k;
     else if(!StrCompare(ch,c3))
       --k;
     ++i;
   }while(i<=n&&StrCompare(ch,c1)||k!=0);
   if(i<=n)
   {
     StrCopy(&ch,*str);
     SubString(hstr,ch,1,i-2);
     SubString(str,ch,i,n-i+1);
   }
   else
   {
     StrCopy(hstr,*str);
     ClearString(str);
   }
   return OK;
 }

 Status CreateGList(GList *L,HString S)
 { /* ����ͷβ�����洢�ṹ,�ɹ��������д��ʽ��S���������L����emp="()" */
   HString emp,sub,hsub;
   GList p,q;
   InitString(&emp);
   InitString(&sub);
   InitString(&hsub);
   StrAssign(&emp,"()");
   if(!StrCompare(S,emp)) /* �����ձ� */
     *L=NULL;
   else
   {
     *L=(GList)malloc(sizeof(GLNode));
     if(!*L) /* ������㲻�ɹ� */
       exit(OVERFLOW);
     if(StrLength(S)==1) /* ������ԭ�ӹ���� */
     {
       (*L)->tag=ATOM;
       (*L)->a.atom=S.ch[0];
     }
     else
     {
       (*L)->tag=LIST;
       p=*L;
       SubString(&sub,S,2,StrLength(S)-2); /* ��������� */
       do /* �ظ���n���ӱ� */
       {
         sever(&sub,&hsub); /* ��sub�з������ͷ��hsub */
         CreateGList(&p->a.ptr.hp,hsub);
         q=p;
         if(!StrEmpty(sub)) /* ��β���� */
         {
           p=(GList)malloc(sizeof(GLNode));
           if(!p)
             exit(OVERFLOW);
           p->tag=LIST;
           q->a.ptr.tp=p;
         }
       }while(!StrEmpty(sub));
       q->a.ptr.tp=NULL;
     }
   }
   return OK;
 }
