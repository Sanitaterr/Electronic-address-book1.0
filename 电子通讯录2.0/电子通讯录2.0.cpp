#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#define contact_max 200
#define account_max 80
#define accountfn_max 30
#define accountname_id_pw_max 20
typedef struct {
	char name[10];
	char sex[5];
	int xh;
	char telnum[13];
}Telinf;
Telinf t;
void use(char acname[accountname_id_pw_max]);//多账户登录(登录，注册，修改密码，找回密码)?
void passwordInput(char* des, int size);//密码输出? 
int ispw(char pw[accountname_id_pw_max]);//密码是否合法? 
void ifgoon();//进行选择是否退出系统 ?
void quit(); //退出系统 ?
void main_meun();//登录菜单 ?
int meun_2();//操作菜单 ?
void selection_interface();//界面颜色选择?
int init(char acname[accountname_id_pw_max], Telinf tel[contact_max]);//导入该账户信息 ?
int add(char acname[accountname_id_pw_max], Telinf tel[contact_max], int len);//添加操作(可一次添加多个联系人信息) ?
int del(char acname[accountname_id_pw_max], Telinf tel[contact_max], int len);//删除操作(支持模糊删除)?
void update(char acname[accountname_id_pw_max], Telinf tel[contact_max], int len);//更新联系人信息(支持模糊查询)?
void search(char acname[accountname_id_pw_max], Telinf tel[contact_max], int len);//查询联系人信息(支持模糊差查询) ?
void show(char acname[accountname_id_pw_max], Telinf tel[contact_max], int len);//显示所有联系人信息?
void sort(char acname[accountname_id_pw_max], Telinf tel[contact_max], int len);//按学号排序 ?
void exported(char acname[accountname_id_pw_max], Telinf tel[contact_max], int len);//导出到表格? 
void clean_account(char acname[accountname_id_pw_max]);//清除账户所有信息? 
int i = 0, j = 0, k = 0;
int main()
{
	Telinf tel[contact_max];
	int length = 0;
	i = 0;
	int choice;
	selection_interface();
	char acname[accountname_id_pw_max];//个人账户名 
	use(acname);
	length = init(acname, tel);
	while (1)
	{
		choice = meun_2();
		switch (choice)
		{
		case 1:length = add(acname, tel, length); ifgoon(); printf("hhh\n"); break;
		case 2:length = del(acname, tel, length); ifgoon(); break;
		case 3:update(acname, tel, length); break;
		case 4:search(acname, tel, length); break;
		case 5:show(acname, tel, length); break;
		case 6:sort(acname, tel, length); break;
		case 7:exported(acname, tel, length); break;
		case 8:clean_account(acname); break;
		case 0:quit(); break;
		default:
		{
			system("cls");
			printf("\t\t\t\t选择无效，请重新选择\n");
			system("PAUSE");
		}
		}
	}
}
void clean_account(char acname[accountname_id_pw_max])
{
	char aname[accountfn_max] = "";
	strcat(aname, acname);
	strcat(aname, ".txt");
	remove(aname);
}
void exported(char acname[accountname_id_pw_max], Telinf tel[contact_max], int len)
{
	system("cls");
	FILE* fp;
	int con;
	strcat(acname, ".csv");
	fp = fopen(acname, "w+");
	fprintf(fp, "%s,%s,%s,%s\n", "姓名", "性别", "学号", "电话号码");
	for (i = 0; i < len; i++)
	{
		fprintf(fp, "%s,%s,%d,%s\n", tel[i].name, tel[i].sex, tel[i].xh, tel[i].telnum);
	}
	fclose(fp);
	printf("导出成功\n");
	ifgoon();
	system("PAUSE");
}
void sort(char acname[accountname_id_pw_max], Telinf tel[contact_max], int len)
{
	system("cls");
	char aname[accountfn_max] = "";
	int con;
	FILE* fp;
	strcat(aname, acname);
	strcat(aname, ".txt");
	fp = fopen(aname, "wt");
	for (i = 0; i < len - 1; i++)
	{
		for (j = 0; j < len - 1 - i; j++)
		{
			if (tel[j].xh > tel[j + 1].xh)
			{
				t = tel[j]; tel[j] = tel[j + 1]; tel[j + 1] = t;
			}
		}
	}//排序完成
	printf("\t\t\t\t-----------------------------------------------------\n");
	printf("\t\t\t\t|姓名      |性别    |学号      |电话号码              |\n");

	for (i = 0; i < len; i++)
	{
		printf("\t\t\t\t|%-10s|%-8s|%-10d|%-20|\n", tel[i].name, tel[i].sex, tel[i].xh, tel[i].telnum);
	}
	printf("\t\t\t\t-----------------------------------------------------\n");
	for (i = 0; i < len; i++)
	{
		fprintf(fp, " %s %s %d %s", tel[i].name, tel[i].sex, tel[i].xh, tel[i].telnum);
	}
	fclose(fp);
	printf("排序完成！！！");
	ifgoon();
	system("PAUSE");
}
void show(char acname[accountname_id_pw_max], Telinf tel[contact_max], int len)
{
	system("cls");
	i = 0;
	int con;
	if (len == 0)
	{
		printf("无联系人信息\n");
	}
	else
	{
		printf("共有%d位联系人\n", len);
		printf("\t\t\t\t-----------------------------------------------------\n");
		printf("\t\t\t\t|姓名      |性别    |学号      |电话号码            |\n");
		for (i = 0; i < len; i++)
		{
			printf("\t\t\t\t|%-10s|%-8s|%-10d|%-20s|\n", tel[i].name, tel[i].sex, tel[i].xh, tel[i].telnum);
		}
		printf("\t\t\t\t-----------------------------------------------------\n");
		printf("已全部显示完毕...\n");
	}
	ifgoon();
}
void search(char acname[accountname_id_pw_max], Telinf tel[contact_max], int len)
{
	system("cls");
	char peo[10];
	int con;
	int c, a[contact_max], b[contact_max], namelen;
	int choice;
	char aname[accountfn_max] = "";
	printf("请输入你要查询的人的姓名：");
	scanf("%s", peo);
	k = 0;
	int peolen = strlen(peo);
	for (i = 0; i < len; i++)
	{
		c = 0;
		namelen = strlen(tel[i].name);
		for (j = 0; j < namelen; j++)
		{
			if (peo[c] == tel[i].name[j])
			{
				c++;
			}

		}
		if (c == peolen)
		{
			k++;
			a[k] = i;
			b[k] = k;
			if (k == 1)
			{
				printf("\t\t\t\t---------------------------------------------------\n");
				printf("\t\t\t\t|序号|姓名      |性别    |学号      |电话号码      |\n");
			}
			printf("\t\t\t\t|%-4d|%-10s|%-8s|%-10d|%-14s\n", k, tel[i].name, tel[i].sex, tel[i].xh, tel[i].telnum);
		}
	}
	if (k > 0)
	{
		printf("\t\t\t\t---------------------------------------------------\n");
	}
	if (k > 0)
	{
		printf("共为您找到%d条相关信息...\n", k);
	}
	if (k == 0)printf("不好意思，未找到相关联系人...\n");
	ifgoon();
	system("PAUSE");
}
void update(char acname[accountname_id_pw_max], Telinf tel[contact_max], int len)
{
	system("cls");
	char peo[10];
	int con;
	int c, a[contact_max], b[contact_max], namelen, flag = 0;
	int choice, choice_2;
	FILE* fp;
	char aname[accountfn_max] = "";
	printf("请输入你要查询的人的姓名：");
	scanf("%s", peo);
	k = 0;
	int peolen = strlen(peo);
	for (i = 0; i < len; i++)
	{
		c = 0;
		namelen = strlen(tel[i].name);
		for (j = 0; j < namelen; j++)
		{
			if (peo[c] == tel[i].name[j])
			{
				c++;
			}
		}
		if (c == peolen)
		{
			k++;
			a[k] = i;
			b[k] = k;
			if (k == 1)
			{
				printf("\t\t\t\t---------------------------------------------------\n");
				printf("\t\t\t\t|序号|姓名      |性别    |学号      |电话号码      |\n");
			}
			printf("\t\t\t\t|%-4d|%-10s|%-8s|%-10d|%-14s\n", k, tel[i].name, tel[i].sex, tel[i].xh, tel[i].telnum);
		}
	}
	if (k > 0)
	{
		printf("\t\t\t\t---------------------------------------------------\n");
	}
	if (k > 0)
	{
		printf("\t\t共搜索到%d个符合条件的联系人，请问您要修改那一位？请输入：", k);
		scanf("%d", &choice);
		for (i = 1; i <= k; i++)
		{
			if (choice == b[i])
			{
				flag = 1;
				printf("\t\t\t\t请选择需要修改的信息：\n");
				printf("1.姓名  2.性别  3.学号  4.电话号码\n");
				scanf("%d", &choice_2);
				if (choice_2 == 1) {
					printf("\t\t将姓名修改为：");
					scanf("%s", tel[a[i]].name);
				}
				else if (choice_2 == 2)
				{
					printf("\t\t将性别修改为：");
					scanf("%s", tel[a[i]].sex);
				}
				else if (choice_2 == 3)
				{
					printf("\t\t将学号修改为：");
					scanf("%d", &tel[a[i]].xh);
				}
				else if (choice_2 == 4)
				{
					printf("\t\t将电话号码修改为：");
					scanf("%s", tel[a[i]].telnum);
				}
			}
			if (flag == 1)break;//修改完成，退出循环 
		}
		strcat(aname, acname);
		strcat(aname, ".txt");
		fp = fopen(aname, "wt");
		for (i = 0; i < len; i++)
		{
			fprintf(fp, " %s %s %d %s", tel[i].name, tel[i].sex, tel[i].xh, tel[i].telnum);
		}
		fclose(fp);
		printf("修改完成!!!");
	}
	if (k == 0)
	{
		printf("不好意思，未找到相关联系人！\n");
	}
	ifgoon();
	system("PAUSE");
}
int del(char acname[accountname_id_pw_max], Telinf tel[contact_max], int len)
{
	char aname[accountfn_max] = "";
	system("cls");
	char peo[10];//删除者姓名 
	i = 0; j = 0; k = 0;//k表示符合条件的人数 
	int a[contact_max], b[contact_max];//a[]储存符合条件被搜索者的序号，b[]储存符合条件的被搜索者的个数 
	int con, choice, c, namelen;
	FILE* fp;
	printf("\t\t请输入你要删除人的姓名：");
	scanf("%s", peo);
	int peoname = strlen(peo);//被删除者姓名长度 
	for (i = 0; i < len; i++)
	{
		namelen = strlen(tel[i].name);//被搜索者姓名长度 
		c = 0;//被搜索者中与被删除者的重复姓名个数 
		for (j = 0; j < namelen; j++)
		{
			if (peo[c] == tel[i].name[j])c++;
		}
		if (c == peoname)//被搜索者包含被删除者姓名的所有字体 
		{
			k++;
			a[k] = i;
			b[k] = k;
			//输出符合条件的被搜索者的信息 
			if (k == 1)
			{
				printf("\t\t\t\t---------------------------------------------------\n");
				printf("\t\t\t\t|序号|姓名      |性别    |学号      |电话号码      |\n");
			}
			printf("\t\t\t\t|%-4d|%-10s|%-8s|%-10d|%-14s|\n", k, tel[i].name, tel[i].sex, tel[i].xh, tel[i].telnum);

		}
	}
	if (k > 0)
	{
		printf("\t\t\t\t---------------------------------------------------\n");
	}
	if (k > 0)
	{
		printf("\t\t共搜索到%d个符合条件的联系人，请问您要删除那一条？请输入：", k);
		scanf("%d", &choice);
		for (i = 1; i <= k; i++)
		{
			if (choice == b[i])
			{
				for (j = a[i]; j < len - 1; j++)
				{
					t = tel[j + 1]; tel[j] = t;
				}
			}
			len = len - 1;
			strcat(aname, acname);
			strcat(aname, ".txt");
			fp = fopen(aname, "wt");
			for (i = 0; i < len; i++)
			{
				fprintf(fp, " %s %s %d %s", tel[i].name, tel[i].sex, tel[i].xh, tel[i].telnum);
			}
			fclose(fp);
			printf("删除成功!!!\n");
		}
	}
	if (k == 0)printf("\t\t很抱歉，查无此人...\n");
	return len;
	system("PAUSE");
}
int add(char acname[accountname_id_pw_max], Telinf tel[contact_max], int len)
{
	system("cls");
	int i = 0, num;
	int con;
	FILE* fp1;
	char aname[accountfn_max] = "";
	printf("\t\t请输入添加个数：");
	scanf("%d", &num);
	for (int i = len; i < num + len; i++)
	{
		printf("\t\t请输入姓名："); scanf("%s", tel[i].name);
		printf("\t\t请输入性别："); scanf("%s", tel[i].sex);
		printf("\t\t请输入学号："); scanf("%d", &tel[i].xh);
		printf("\t\t请输入联系电话："); scanf("%s", tel[i].telnum);
	}
	strcat(aname, acname); strcat(aname, ".txt");
	fp1 = fopen(aname, "at");
	for (i = len; i < num + len; i++)
	{
		fprintf(fp1, " %s %s %d %s", tel[i].name, tel[i].sex, tel[i].xh, tel[i].telnum);
	}
	fclose(fp1);
	len = len + num;
	return len;
}
int meun_2()
{
	int choice;
	system("cls");
	printf("\t\t\t\t************************************\n");
	printf("\t\t\t\t*      欢迎使用电子通讯录          *\n");
	printf("\t\t\t\t*  1.添加联系人                    *\n");
	printf("\t\t\t\t*  2.删除联系人                    *\n");
	printf("\t\t\t\t*  3.修改联系人信息                *\n");
	printf("\t\t\t\t*  4.查询联系人信息                *\n");
	printf("\t\t\t\t*  5.显示所有联系人信息            *\n");
	printf("\t\t\t\t*  6.按学号排序                    *\n");
	printf("\t\t\t\t*  7.导出                          *\n");
	printf("\t\t\t\t*  8.清空该账户                    *\n");
	printf("\t\t\t\t*  0.退出本系统                    *\n");
	printf("\t\t\t\t************************************\n");
	printf("\t\t请输入你的选择：");
	scanf("%d", &choice);
	return choice;
}
int init(char acname[accountname_id_pw_max], Telinf tel[contact_max])
{
	int i = 0;
	FILE* fp;
	char aname[accountfn_max] = "";
	strcat(aname, acname);
	strcat(aname, ".txt");
	fp = fopen(aname, "rt");
	if (fp != NULL)
	{
		while (fscanf(fp, " %s %s %d %s", tel[i].name, tel[i].sex, &tel[i].xh, tel[i].telnum) != EOF)
		{
			i++;
		}
		fclose(fp);
	}
	printf("\t\t%s，欢迎回来！\n", aname);
	printf("\t\t您有%d信息在本通讯录中...\n", i);
	return i;
}
void selection_interface()
{
	int choice;
	printf("\t\t选择你喜欢的界面颜色吧！\n");
	printf("\t您有4种选择模式：\n");
	printf("\t1.白底黑字\n\t2.黑底白字\n\t3.蓝底白字\n\t4.绿底黑字\n");
	printf("请输入对应数字：");
	scanf("%d", &choice);
	switch (choice)
	{
	case 1:system("color 70"); break;
	case 2:system("color 07"); break;
	case 3:system("color 97"); break;
	case 4:system("color B0"); break;
	default:printf("已默认为你选择黑底白字"); break;
	}
}
int ispw(char pw[accountname_id_pw_max])
{
	int number = 0, len = strlen(pw);
	if (len < 8)
	{
		printf("\t长度不符合规则，请重新输入!\n");
		return 0;
	}
	for (int i = 0; i < len; i++)
	{
		if (pw[i] >= '0' && pw[i] <= '9')number++;
	}
	if (number == len)
	{
		printf("\t密码内只含有数字，请重新输入！\n");
		return 0;
	}
	return 1;
}
void main_meun() {
	printf("\t\t\t\t—————————————————————\n");
	printf("\t\t\t\t|          欢迎使用电子通信录             |\n");
	printf("\t\t\t\t|   1.登录                                |\n");
	printf("\t\t\t\t|   2.注册                                |\n");
	printf("\t\t\t\t|   3.找回密码                            |\n");
	printf("\t\t\t\t|   4.修改密码                            |\n");
	printf("\t\t\t\t|   5.退出系统                            |\n");
	printf("\t\t\t\t—————————————————————\n");
}
void use(char acname[accountname_id_pw_max])
{
	system("cls");
	struct registers
	{
		char id[accountname_id_pw_max];
		char pw[accountname_id_pw_max];//长度为accountname_id_pw_max的密码 
	}acr[account_max];//结构体数组里,有账号密码
	int length;
	char udpw[accountname_id_pw_max], udid[accountname_id_pw_max], newpw[accountname_id_pw_max], newpw_2[accountname_id_pw_max];//修改密码 
	char idblack[account_max][accountname_id_pw_max], pwblack[account_max][accountname_id_pw_max];//修改密码 
	int con;//是否继续
	int cou;//密保
	int c = 0;
	int choice;//选择 
	i = 0; j = 0; k = 0;
	int flag = 0;//是否有数据在文件中 
	char idd[account_max][accountname_id_pw_max], pww[account_max][accountname_id_pw_max];
	char id_reg[accountname_id_pw_max], qst[accountname_id_pw_max], ans[accountname_id_pw_max], oldid[account_max][accountname_id_pw_max], oldpw[account_max][accountname_id_pw_max], secret_qst[account_max][accountname_id_pw_max], secret_ans[account_max][accountname_id_pw_max];
	FILE* fp1;
	FILE* fp2;
	FILE* fp3;
	FILE* fp4;
	main_meun();//显示登录界面 
	printf("\t请选择：");
	scanf("%d", &choice);
	if (choice == 1)
	{
		fp1 = fopen("id.txt", "rt");
		fp2 = fopen("pw.txt", "rt");//读取文件id和pw的信息
		if (fp1 != NULL)
		{
			flag = 1;
			while (fscanf(fp1, " %s", idd[k]) != EOF)
			{
				k++;
			}//将文件里id导入 
			k = 0;
			while (fscanf(fp2, " %s", pww[k]) != EOF)
			{
				k++;
			}//将文件里导入 
		}
		else {
			printf("\t\t请先注册，再使用本系统,将自动为你跳转注册界面\n");
			choice = 2;
		}
		if (flag)//保证系统有数据，开始下列操作 
		{
			for (i = 0; i < 3; i++)//最多试三次密码 
			{
				printf("\t请输入账号：");
				scanf("%s", acr[i].id);//输入密码，并保存在结构体数组里 
				fflush(stdin);
				printf("\t请输入密码：");
				while (1)
				{
					passwordInput(acr[i].pw, accountname_id_pw_max);
					if (ispw(acr[i].pw))break;
					printf("\t请重新输入密码：");
				}
				for (j = 0; j < k; j++)
				{
					if ((strcmp(idd[j], acr[i].id) == 0) && (strcmp(pww[j], acr[i].pw) == 0))
					{
						break;
					}//找到账号与密码同时符合的就退出循环，停止查找。 
				}
				if (j < k)break;//找到就退出输入密码环节
				else if (i != 2)printf("\t账号或密码错误！您还可以输入%d次！\n", 2 - i);
				else printf("\t很遗憾，输入错误已达3次，您可以选择找回密码...");
			}
			if (i == 3)choice = 5;
			if (i < 3 && j < k)
			{
				printf("\t\t登陆成功！\n");
				strcpy(acname, acr[i].id);//acname为登录用户id
				ifgoon();
			}
		}
		fclose(fp1); fclose(fp2);//关闭id和pw文件 	
	}
	if (choice == 2)
	{
		k = 0;
		fp1 = fopen("id.txt", "rt");//导入账号 
		while (fscanf(fp1, " %s", acr[k].id) != EOF)
		{
			k++;//账号数据条数 
		}
		fclose(fp1);//账号导入完毕 
		printf("\t\t恭喜你成为该使用系统的第%d位用户\n", k + 1);
		printf("\t\t\t\t开始注册！\n");
		printf("\t请输入账号：");
		fflush(stdin);
		while (1)
		{
			c = 0;//统计与原账户的记录不相同数量 
			scanf("%s", id_reg);
			for (i = 0; i < k; i++)
			{
				if (strcmp(id_reg, acr[i].id) != 0)
				{
					c++;
				}
			}
			if (c == k)break;
			else printf("\t账号已注册，请重新输入！:");
		}
		printf("\t\t账号设置成功！\n");
		printf("\t密码要求：1.长度不小于8   2.不能只包含数字\n");
		while (1)
		{
			printf("\t请输入密码：");
			while (1)
			{
				passwordInput(acr[0].pw, accountname_id_pw_max);
				if (ispw(acr[0].pw) == 1)break;
				printf("\t请重新输入密码：");
			}
			printf("\t密码已设置，请重新输入密码：");
			passwordInput(acr[1].pw, accountname_id_pw_max);
			if (strcmp(acr[0].pw, acr[1].pw) == 0)break;
			else printf("\n\t\t两次密码不一致，请重新输入！\n");
		}
		fp3 = fopen("secretquestion.txt", "at");
		fp4 = fopen("secretanswer.txt", "at");
		fflush(stdin);
		printf("\n");
		printf("\t请输入你的密保问题：");
		scanf("%s", qst); fflush(stdin);
		printf("\t请输入你的密保答案：");
		scanf("%s", ans); fflush(stdin);//输入密保问题和答案 
		fprintf(fp3, " %s", qst);
		fprintf(fp4, " %s", ans);
		fclose(fp3); fclose(fp4);

		fp1 = fopen("id.txt", "at"); fp2 = fopen("pw.txt", "at");

		fprintf(fp1, " %s", id_reg); fprintf(fp2, " %s", acr[0].pw);

		printf("\t\t\t\t注册完成！！！\n");
		strcpy(acname, acr[0].id);
		fclose(fp1); fclose(fp2);
		ifgoon();
	}
	if (choice == 3)
	{
		fp1 = fopen("id.txt", "rt");
		i = 0;
		while (fscanf(fp1, " %s", oldid[i]) != EOF)
		{
			i++;
		}
		fclose(fp1);
		printf("\t请输入您的账号:");
		scanf("%s", id_reg);
		for (j = 0; j < i; j++)
		{
			if (strcmp(id_reg, oldid[j]) == 0)
			{
				break;
			}
		}
		if (j == i)
		{
			printf("\t\t\t\t账号错误\n");
			choice = 5;
		}//输入账号在文件中未找到 
		else
		{
			printf("\t\t\t\t账号输入正确！\n");
			fp3 = fopen("secretquestion.txt", "rt");
			fp4 = fopen("secretanswer.txt", "rt");
			k = 0;
			while (fscanf(fp3, "%s", secret_qst[k]) != EOF)
			{
				k++;
			}
			k = 0;
			while (fscanf(fp4, "%s", secret_ans[k]) != EOF)
			{
				k++;
			}
			fclose(fp3); fclose(fp4);
			printf("\t密保问题：%s\n", secret_qst[j]);
			printf("\t请输入密保答案:");
			scanf("%s", ans);
			if (strcmp(ans, secret_ans[j]) == 0)//密保的答案正确 
			{
				fp2 = fopen("pw.txt", "rt");
				for (k = 0; k < i; k++)//导入oldpw文件密码 
				{
					fscanf(fp2, " %s", oldpw[k]);
				}
				fclose(fp2);
				printf("\t\t你的密码是：%s\n", oldpw[j]);
				ifgoon();
			}
			if (strcmp(ans, secret_ans[j]) != 0)
			{
				printf("\t\t密保答案错误\n");
				choice = 5;
			}
		}
	}
	if (choice == 4)
	{
		printf("\t请输入您要修改的密码的账号:");
		scanf("%s", udid);//修改的密码账号 
		fp1 = fopen("id.txt", "rt");
		fp2 = fopen("pw.txt", "rt");
		k = 0;
		while (fscanf(fp1, " %s", idblack[k]) != EOF)
		{
			k++;
		}//将文件中的账号导入到idblack 
		k = 0;
		while (fscanf(fp2, " %s", pwblack[k]) != EOF)
		{
			k++;
		}//将文件中的密码导入到pwblack 
		fclose(fp1); fclose(fp2);
		for (i = 0; i < k; i++)//是否找到账号 ,若找到，该账号为idblack[i]
		{
			if (strcmp(idblack[i], udid) == 0)break;
		}
		if (i == k)
		{
			printf("\t\t账号输入错误！\n");
			choice = 5;
		}
		if (i < k)//找到该账号 
		{
			printf("\t\t账号输入正确！\n");
			fp3 = fopen("secretquestion.txt", "rt");
			fp4 = fopen("secretanswer.txt", "rt");
			for (j = 0; j < k; j++)
			{
				fscanf(fp3, " %s", secret_qst[j]);
				fscanf(fp4, " %s", secret_ans[j]);
			}//将密保问题和密保答案保存在secret_qst数组和secret_ans数组 
			fclose(fp3); fclose(fp4);
			printf("\t问题：%s\n", secret_qst[i]);
			printf("\t请输入你的密保答案：");
			scanf("%s", ans);
			if (strcmp(ans, secret_ans[i]) == 0)
			{
				printf("\t\t\t\t回答正确！\n");
				while (1)
				{
					while (1)
					{
						printf("\t请输入新密码：");
						passwordInput(newpw, accountname_id_pw_max);
						if (ispw(newpw) == 1)
						{
							break;
						}
					}
					printf("\t请再次输入密码：");
					fflush(stdin);
					passwordInput(newpw_2, accountname_id_pw_max);
					if (strcmp(newpw_2, newpw) == 0)
						break;
					else printf("\t密码不一致，请重新输入！\n");
				}
				strcpy(pwblack[i], newpw);
				fp2 = fopen("pw.txt", "wt");
				for (j = 0; j < k; j++)
				{
					fprintf(fp2, "%s", pwblack[i]);
				}
				fclose(fp2);
				printf("\t\t\t\t密码修改成功！\n");
				ifgoon();
			}
			else
			{
				printf("\t\t\t\t回答错误!!!\n");
				choice = 5;
			}
		}

	}
	if (choice == 5)
	{
		puts("");
		printf("\t\t\t\t感谢使用本通讯录!\n");
		exit(0);
	}
	if (choice > 5)
	{
		printf("\t\t请正确输入。。。");
		exit(0);
	}
}

void quit() {
	printf("\n");
	printf("\t\t\t\t感谢使用，下次再见！\n");
	system("PAUSE");
	system("cls");
	exit(0);
}
void passwordInput(char* des, int len)
{
	int al = 0;
	char c;
	while (al < len)
	{
		c = getch();
		if (c == '\b' && al > 0)
		{
			printf("\b");
			printf(" ");
			printf("\b");
			al--;
		}
		else
		{
			if (c == '\r')
			{
				des[al++] = 0;
				break;
			}
		}
		des[al++] = c;
		printf("*");
	}
}
void ifgoon()
{
	printf("\n");
	printf("\t是否继续： 1.继续  2.退出系统\n");
	int choice;
	printf("请选择：");
	scanf("%d", &choice);
	if (choice == 2)
	{
		quit();
	}
}


