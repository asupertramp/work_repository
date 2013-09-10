 /* bo5-3.c ���߼�����ϡ�����(�洢�ṹ��c5-3.h����)�Ļ�������(8��) */
 Status CreateSMatrix(RLSMatrix *M)
 { /* ����ϡ�����M */
   int i;
   Triple T;
   Status k;
   printf("��������������,����,����Ԫ������");
   scanf("%d,%d,%d",&(*M).mu,&(*M).nu,&(*M).tu);
   (*M).data[0].i=0; /* Ϊ���±Ƚ���׼�� */
   for(i=1;i<=(*M).tu;i++)
   {
     do
     {
       printf("�밴����˳�������%d������Ԫ�����ڵ���(1��%d),��(1��%d),Ԫ��ֵ��",i,(*M).mu,(*M).nu);
       scanf("%d,%d,%d",&T.i,&T.j,&T.e);
       k=0;
       if(T.i<1||T.i>(*M).mu||T.j<1||T.j>(*M).nu) /* �С��г�����Χ */
         k=1;
       if(T.i<(*M).data[i-1].i||T.i==(*M).data[i-1].i&&T.j<=(*M).data[i-1].j) /* û�а�˳���������Ԫ�� */
         k=1;
     }while(k); /* ����������,�������� */
     (*M).data[i]=T;
   }
   for(i=1;i<=(*M).tu;i++) /* ����rpos[] */
     if((*M).data[i].i>(*M).data[i-1].i)
       for(T.i=0;T.i<(*M).data[i].i-(*M).data[i-1].i;T.i++)
         (*M).rpos[(*M).data[i].i-T.i]=i;
   for(i=(*M).data[(*M).tu].i+1;i<=(*M).mu;i++) /* �����û�з���Ԫ�صļ��и�ֵ */
     (*M).rpos[i]=(*M).tu+1;
   return OK;
 }

 void DestroySMatrix(RLSMatrix *M)
 { /* ����ϡ�����M(ʹMΪ0��0��0������Ԫ�صľ���) */
   (*M).mu=0;
   (*M).nu=0;
   (*M).tu=0;
 }

 void PrintSMatrix(RLSMatrix M)
 { /* ���ϡ�����M */
   int i;
   printf("%d��%d��%d������Ԫ�ء�\n",M.mu,M.nu,M.tu);
   printf("��  ��  Ԫ��ֵ\n");
   for(i=1;i<=M.tu;i++)
     printf("%2d%4d%8d\n",M.data[i].i,M.data[i].j,M.data[i].e);
   for(i=1;i<=M.mu;i++)
     printf("��%d�еĵ�һ������Ԫ���Ǳ������%d��Ԫ��\n",i,M.rpos[i]);
 }

 Status CopySMatrix(RLSMatrix M,RLSMatrix *T)
 { /* ��ϡ�����M���Ƶõ�T */
   *T=M;
   return OK;
 }

 Status AddSMatrix(RLSMatrix M,RLSMatrix N,RLSMatrix *Q)
 { /* ��ϡ�����ĺ�Q=M+N */
   int k,p,q;
   if(M.mu!=N.mu||M.nu!=N.nu)
     return ERROR;
   (*Q).mu=M.mu;
   (*Q).nu=M.nu;
   (*Q).tu=0;
   M.rpos[M.mu+1]=M.tu+1; /* Ϊ��������whileѭ����ʱ���� */
   N.rpos[N.mu+1]=N.tu+1;
   for(k=1;k<=M.mu;++k) /* ����ÿһ�У�kָʾ�к� */
   {
     (*Q).rpos[k]=(*Q).tu+1;
     p=M.rpos[k]; /* pָʾM�����k�е�ǰԪ�ص���� */
     q=N.rpos[k]; /* qָʾN�����k�е�ǰԪ�ص���� */
     while(p<M.rpos[k+1]&&q<N.rpos[k+1])
     { /* M,N������е�k��Ԫ��δ���� */
       if(M.data[p].j==N.data[q].j) /* M����ǰԪ�غ�N����ǰԪ�ص�����ͬ */
       {
         (*Q).data[(*Q).tu+1].e=M.data[p].e+N.data[q].e;
         if((*Q).data[(*Q).tu+1].e!=0)
         {
           ++(*Q).tu;
           (*Q).data[(*Q).tu].i=k;
           (*Q).data[(*Q).tu].j=M.data[p].j;
         }
         ++p;
         ++q;
       }
       else if(M.data[p].j<N.data[q].j)
       { /* M����ǰԪ�ص���<N����ǰԪ�ص��� */
         ++(*Q).tu;
         (*Q).data[(*Q).tu].e=M.data[p].e;
         (*Q).data[(*Q).tu].i=k;
         (*Q).data[(*Q).tu].j=M.data[p].j;
         ++p;
       }
       else /* M����ǰԪ�ص���>N����ǰԪ�ص��� */
       {
         ++(*Q).tu;
         (*Q).data[(*Q).tu].e=N.data[q].e;
         (*Q).data[(*Q).tu].i=k;
         (*Q).data[(*Q).tu].j=N.data[q].j;
         ++q;
       }
     }
     while(p<M.rpos[k+1]) /* M������k�е�Ԫ��δ���� */
     {
       ++(*Q).tu;
       (*Q).data[(*Q).tu].e=M.data[p].e;
       (*Q).data[(*Q).tu].i=k;
       (*Q).data[(*Q).tu].j=M.data[p].j;
       ++p;
     }
     while(q<N.rpos[k+1]) /* N������k�е�Ԫ��δ���� */
     {
       ++(*Q).tu;
       (*Q).data[(*Q).tu].e=N.data[q].e;
       (*Q).data[(*Q).tu].i=k;
       (*Q).data[(*Q).tu].j=N.data[q].j;
       ++q;
     }
   }
   return OK;
 }

 Status SubtSMatrix(RLSMatrix M,RLSMatrix N,RLSMatrix *Q)
 { /* ��ϡ�����Ĳ�Q=M-N */
   int i;
   if(M.mu!=N.mu||M.nu!=N.nu)
     return ERROR;
   for(i=1;i<=N.tu;++i) /* ����N��ÿһԪ��,��ֵ����-1 */
     N.data[i].e*=-1;
   AddSMatrix(M,N,Q); /* Q=M+(-N) */
   return OK;
 }

 Status MultSMatrix(RLSMatrix M,RLSMatrix N,RLSMatrix *Q)
 { /* ��ϡ�����˻�Q=M��N���㷨5.3 */
   int arow,brow,p,q,ccol,ctemp[MAXRC+1];
   if(M.nu!=N.mu) /* ����M������Ӧ�;���N��������� */
     return ERROR;
   (*Q).mu=M.mu; /* Q��ʼ�� */
   (*Q).nu=N.nu;
   (*Q).tu=0;
   M.rpos[M.mu+1]=M.tu+1; /* Ϊ��������whileѭ����ʱ���� */
   N.rpos[N.mu+1]=N.tu+1;
   if(M.tu*N.tu!=0) /* M��N���Ƿ������ */
   {
     for(arow=1;arow<=M.mu;++arow)
     { /* ��M�ĵ�һ�п�ʼ�������һ�У�arow��M�ĵ�ǰ�� */
       for(ccol=1;ccol<=(*Q).nu;++ccol)
         ctemp[ccol]=0; /* Q�ĵ�ǰ�еĸ���Ԫ���ۼ������� */
       (*Q).rpos[arow]=(*Q).tu+1; /* Q��ǰ�еĵ�1��Ԫ��λ����1�����1��Ԫ��֮�� */
       for(p=M.rpos[arow];p<M.rpos[arow+1];++p)
       { /* ��M��ǰ����ÿһ������Ԫ */
         brow=M.data[p].j; /* �ҵ���ӦԪ��N�е��к�(M��ǰԪ���к�) */
         for(q=N.rpos[brow];q<N.rpos[brow+1];++q)
	 {
           ccol=N.data[q].j; /* �˻�Ԫ����Q���к� */
           ctemp[ccol]+=M.data[p].e*N.data[q].e;
         }
       } /* ���Q�е�arow�еķ���Ԫ */
       for(ccol=1;ccol<=(*Q).nu;++ccol) /* ѹ���洢���з���Ԫ */
         if(ctemp[ccol])
         {
           if(++(*Q).tu>MAXSIZE)
             return ERROR;
           (*Q).data[(*Q).tu].i=arow;
           (*Q).data[(*Q).tu].j=ccol;
           (*Q).data[(*Q).tu].e=ctemp[ccol];
         }
     }
   }
   return OK;
 }

 Status TransposeSMatrix(RLSMatrix M,RLSMatrix *T)
 { /* ��ϡ�����M��ת�þ���T */
   int p,q,t,col,*num;
   num=(int *)malloc((M.nu+1)*sizeof(int));
   (*T).mu=M.nu;
   (*T).nu=M.mu;
   (*T).tu=M.tu;
   if((*T).tu)
   {
     for(col=1;col<=M.nu;++col)
       num[col]=0;  /* ���ֵ */
     for(t=1;t<=M.tu;++t) /* ��M��ÿһ�з���Ԫ���� */
       ++num[M.data[t].j];
     (*T).rpos[1]=1;
     for(col=2;col<=M.nu;++col) /* ��M�е�col�е�һ������Ԫ��(*T).data�е���� */
       (*T).rpos[col]=(*T).rpos[col-1]+num[col-1];
     for(col=1;col<=M.nu;++col)
       num[col]=(*T).rpos[col];
     for(p=1;p<=M.tu;++p)
     {
       col=M.data[p].j;
       q=num[col];
       (*T).data[q].i=M.data[p].j;
       (*T).data[q].j=M.data[p].i;
       (*T).data[q].e=M.data[p].e;
       ++num[col];
     }
   }
   free(num);
   return OK;
 }