#define _CRT_SECURE_NO_WARNINGS  //在VS中使用 避免出现scanf printf不安全的警告
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>
//#define MAX_LEN 100 
#define LEN1 sizeof(struct patient)
#define LEN2 sizeof(struct pharmaceuticals)
#define LEN3 sizeof(struct doctor)

char account_admin[10] = "admin"; //管理员初始账号
char passward_admin[10] = "12345"; //管理员初始密码
char account_docter[10] = "doctor"; //医生初始账号
char passward_doctor[10] = "12345"; //医生初始密码
char account_user[10] = "user";  //用户初始账号
char passward_user[10] = "12345"; //用户初始密码

typedef struct patient { //定义病人结构体
	char name[20];          //姓名
	char sex[15];           //性别
	char year[10];          //年龄
	char ID[1000];         //身份证号
	char time[100];        //入院时间
	char disease[1000];    //病症
	char pay[100];         //付费方式
	char department[20];    //科室
	char doctor[100];       //主治医生
	char phone[15];         //手机号
	char number[15];        //床号
	char orders[1000];     //医嘱
	char dependents[100];    //家属
	char depend_phone[1000];//家属联系方式
	char pharmaceuticals[1000];//药品
	char adverse_reactions[1000];//不良反应
	struct patient* next;    //病人结构体指针
} pat;
pat* head1;
struct patient* p1;

typedef struct pharmaceuticals { //定义药品结构体
	char name[1000];               //药品名称
	int price;                      //药品价格（元）
	char origin[1000];             //药品产地
	char money[1000];               //药品总价
	struct pharmaceuticals* next;           //药品结构体指针
} pha;
pha* head2;
struct pharmaceuticals* p2;

typedef struct doctor { //定义医生结构体
	char number[1000];       //医生编号
	char name[100];          //医生姓名
	char department[20];     //科室
	char excle[1000];        //医生擅长病症
	struct doctor* next;      //医生结构体指针
} doc;
doc* head3;
struct doctor* p3;

int inter();                        //密码进入界面
void interface_admin();              //管理员界面
int interface_begin();               //起始界面
void interface_user();               //用户界面
int interface_doctor();             //医生界面
void revise();                      //修改界面
void input();                       //输入界面
void look();                        //显示界面
void insert();                      //插入界面
void interface_delete();            //删除界面
void interface_look();              //查看界面
void interface_save();              //保存界面
void revise_passward();             //密码修改界面
doc* inputdata_doc();                   //输入医生
pat* input_patient(pat* head1);       //p1 输入病人数据
pha* input_pharmaceuticals(pha* head2); //输入药品 p2
pat* adverse_reactions(pat* head1);      //输入不良反应
pat* orders(pat* head1);                //输入医嘱
pat* pha_pat_doc(pat* head1);            //医生输入药品
pat* lookdate_orders(pat* p1);         //查看医嘱
pat* lookdate_reactions(pat* p1);       //查看不良反应
pat* lookdata_pat(pat* p1);        //查看病人数据的函数
pha* lookdate_pha(pha* p2);        //查看药品数据的函数
doc* lookdate_doc(doc* p3);        //查看医生数据的函数
pat* look_pat_pha(pat* p1);       //查看病人药品
void update_pha_pat(pat* p1);      //查找病人修改药品数据
void find_ID_doc(doc* p3);        //按编号查找医生
void find_dep_doc(doc* p3);       //按科室查找医生
void revise_admin();               //管理员密码,账号修改
void revise_doctor();              //医生初始密码,账号修改
void revise_user();               //病人密码,账号修改
void insert();                     //插入数据
void find(pat* p1);                //通过姓名查找查看数据的函数
void find_ID(pat* p1);             //身份证
void find_depart(pat* p1);        //科室
void find_bed(pat* p1);          //病床
void add_pat(struct patient* head1);         //插入病人数据
void add_pha(struct pharmaceuticals* head2); //插入药品数据
void insert_doctor(struct doctor* head3);    //插入医生数据
void update_patient(pat* p2);                //查找病人修改数据
void update_doctor(doc* p3);                 //查找医生修改数据
void update_pharmaceuticals(pha* p2);        //查找药品修改数据
int screen();                    //主界面
void deleted_patient();          //删除病人数据
void deleted_doctor();           //删除医生数据
void deleted_pharmaceuticals();  //删除药品数据
void save_patient(pat* head1);         //保存病人信息
void save_pharmaceuticals(pha* head2); //保存药品信息
void save_doctor(doc* head3);          //保存医生信息
struct patient* readpat(struct patient* head1);//病人读出
struct doctor* readdoc(struct doctor* head3);  //医生读出
struct pharmaceuticals* readpha(struct pharmaceuticals* head2);//药品读出
void* Sort(struct patient* head1);    //排序

int main() { //主函数 
	readpat(head1);
	readdoc(head3);
	readpha(head2);
	screen();
	Sleep(3000);

	if (inter() == -1) {
		//   if  (i==-1) {
		printf("输入次数已经用尽，系统将自动退出！\n");
		exit(1);
	}
	return 0;
}
//ok
int screen() { //屏幕
	int i;
	char s[251] = { "		欢迎使用医院病人管理系统\n\n\t\t\t		祝您家庭美满,身体健康!\n\n\n\t\t" };
	//printf("\n================================================================================\n");
	printf("\n\n\n\t\t\t");
	for (i = 0; s[i] != '\0'; i++) {
		Sleep(38);
		printf("%c", s[i]);
	}
	inter();
	printf("\n\n\n\n\n\n\n\n\t\t ~ 病人无医 将陷于无望 病人无护 将陷于无助 ~ \n");
	printf("================================================================================\n");
	return 0;
}
//ok
int inter() { //密码进入
	system("cls");	//清屏 
	int i = 5;
	char  account[10] = { 0 };
	char passward[10] = { 0 };//password
	printf("   ********欢迎使用医院管理系统*********\n");
	printf("      志在救人，剂温凉寒暖，而万姓感德\n");
	printf("      心欲济世，诊沉浮迟数，乃千古扬庥\n");
	printf("----------------------------------------------------------\n");
	while (i) {
		printf("请输入您的账号: ");
		scanf("%s%*c", account);
		printf("请输入您的密码: ");
		scanf("%s%*c", passward);
		if (strcmp(account, account_admin) == 0 && strcmp(passward, passward_admin) == 0) {
			interface_admin();   //管理员界面
			break;
		}
		else if (strcmp(account, account_docter) == 0 && strcmp(passward, passward_doctor) == 0) {
			interface_doctor();   //医生界面
			break;
		}
		else if (strcmp(account, account_user) == 0 && strcmp(passward, passward_user) == 0) {
			interface_user();     //用户界面
			break;
		}
		else {
			i--;
			printf("密码输入错误\n请重新输入(您还剩下%d次机会)\n", i);
		}
	}
	if (i == 0) {
		return -1;
	}
	return 0;
}
//ok
void interface_admin() { //管理员界面
	system("cls");
	printf("☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆\n");
	printf("*****************************************************************\n");
	printf("*    \t\t医院病人管理系统(管理员界面）			*\n");
	printf("*								*\n");
	printf("*      \t\t1. 输入数据");
	printf("\t\t2. 显示数据		*\n");
	printf("*      \t\t3. 插入数据");
	printf("\t\t4. 删除数据		*\n");
	printf("*      \t\t5. 查看数据");
	printf("\t\t6. 修改数据		*\n");
	printf("*      \t\t7. 返回主菜单");
	printf("\t\t8.退出			*\n");
	printf("*\t\t\t9.密码修改   				*\n");
	printf("*								*\n");
	printf("*****************************************************************\n");
	printf("-------------------------------------------------------------------------\n");
	int ans;
	printf("请输入你的选择(1~9):");
	while (~scanf("%d%*c", &ans))
		if (ans < 1 || ans > 9)
			printf("输入有误,请在1~9中进行选择:\n");
		else break;
	switch (ans) {
	case 1:
		input();
		break;
	case 2:
		look();
		break;
	case 3:
		insert();
		break;
	case 4:
		interface_delete();
		break;
	case 5:
		interface_look();
		break;
	case 6:
		revise();
		break;
	case 7:
		screen();
		break;
	case 8:
		exit(1);
		break;
	case 9:
		revise_passward();
		break; 
	}
}
//ok
void interface_user() { //用户界面
	system("cls");
	int ans;
	printf("☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆\n");
	printf("*************************************************************************\n");
	printf("*      \t\t医院病人管理系统(用户界面）				*\n");
	printf("*									*\n");
	printf("*             \t\t 1.查看个人信息					*\n");
	printf("*             \t\t 2.查看医生情况					*\n");
	printf("*             \t\t 3.查看药品情况					*\n");
	printf("*             \t\t 4.不良反应反馈					*\n");
	printf("*             \t\t 5.查看医嘱					*\n");
	printf("*             \t\t 6.修改密码					*\n");
	printf("*             \t\t 0.返回主菜单					*\n");
	printf("*************************************************************************\n");
	printf("===============================================================================\n");
	printf("请输入(0~6):");
	fflush(stdin);
	while (~scanf("%d", &ans))
		if (ans < 0 || ans > 6)
			printf("输入有误,请在0~6中进行选择:\n");
		else break;
	switch (ans) {
	case 1:
		system("cls");
		printf("输入0返回界面\n");
		printf("\n\t\t\t☆☆☆查看数据☆☆☆\n");
		find_bed(head1);  //查看病人信息
		break;
	case 2:
		system("cls");
		printf("\n\t\t\t☆☆☆查看数据(输入1返回界面)☆☆☆\n");
		find_ID_doc(head3);  //按编号查看医生
		break;
	case 3:
		look_pat_pha(head1);//查看病人药品
		break;
	case 4:
		adverse_reactions(head1);//输入不良反应
		break;
	case 5:
		lookdate_orders(head1);
		break;
	case 6:
		 revise_user();
		 break; 
	case 0:
		screen();
		break;
	}
}
//ok
int interface_doctor() { //医生界面
	system("cls");
	int ans;
	printf("☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆\n");
	printf("☆\t我决心竭尽全力除人类之病痛，助健康之完美，维护医术的圣洁和荣誉	          	☆\n");
	printf("☆\t救死扶伤,不辞艰辛,执着追求,为祖国医药卫生事业的发展和人类身心健康奋斗终生!	☆\n");
	printf("☆                         1.查看所有病人						☆\n");    
	printf("☆                         2.按照身份证号查找病人					☆\n");
	printf("☆                         3.按照病床号查看病人  					☆\n");  
	printf("☆                         4.查看科室中病人信息						☆\n"); 
	printf("☆                         5.输入药品信息						☆\n");      
	printf("☆                         6.修改药品信息						☆\n");       
	printf("☆                         7.添加医嘱							☆\n");           
	printf("☆                         8.修改医嘱							☆\n");      
	printf("☆                         9.查看科室中病人不良反应记录					☆\n");
	printf("☆                         10.修改密码							☆\n");
	printf("☆                         0.返回主界面							☆\n");
	printf("☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆\n");
	printf("---------------------------------------------------------------------------------------------\n");
	printf("请输入你的选项(0~10): \n");
	while (~scanf("%d%*c", &ans))
		if (ans < 0 || ans > 10)
			printf("输入有误,请在0~10中进行选择:\n");
		else break;
	switch (ans) {
	case 1:
		system("cls");
		printf("\n\t\t\t☆☆☆显示病人数据☆☆☆\n");
		printf("输入0返回界面\n");
		head1 = lookdata_pat(head1);
		break;
	case 2:
		system("cls");
		printf("\n\t\t\t☆☆☆查看数据☆☆☆\n");
		printf("返回界面请输0\n");
		find_ID(head1);                     //按照身份证号找
		break;
	case 3:
		system("cls");
		printf("\n\t\t\t☆☆☆查看数据(输入1返回界面)☆☆☆\n");
		find_bed(head1);                    //按照病床号查找
		break;
	case 4:
		find_depart(head1);                //按照科室查找病人p1
		break;
	case 6:
		update_pha_pat(head1);              //查找病人修改药品数据
		break;
	case 5:
		pha_pat_doc(head1);                 //医生输入药品
		break;
	case 7:
		orders(head1);                     //输入不良反应
		break;
	case 8:
		update_patient(head1);             //修改医嘱
		break;
	case 9:
		lookdate_reactions(p1);            //查看不良反应
		break;
	case 10:
		 revise_doctor();
		 break; 
	case 0:
		screen();
		break;
	}
	return 0;
}
//ok
void revise() { //修改界面
	system("cls");
	int ans;
	printf("欢迎进入修改界面(输入“0”返回主界面)	:			\n");
	printf("\n");
	printf("*********************************************************\n");
	printf("*                1.病人信息修改				*\n");
	printf("*                2.医生信息修改				*\n");
	printf("*                3.药品信息修改				*\n");
	printf("*********************************************************\n");
	printf("-------------------------------------------------------------\n");
	printf("请输入您所需要的选项：");
	
	while (~scanf("%d%*c", &ans))
		if (ans < 0 || ans > 3)
			printf("输入有误,请在0~3中进行选择:\n");
		else break;
	switch (ans) {
	case 1:
		update_patient(head1);
		break;
	case 2:
		update_doctor(head3);
		break;
	case 3:
		update_pharmaceuticals(head2);
		break;
	case 0:
		interface_admin();
		break;
	}
}
//ok
void input() { //输入界面
	system("cls");
	int ans;
	printf("欢迎进入输入界面(输入“0”返回主界面):				\n");
	printf("\n");
	printf("*********************************************************\n");
	printf("*                1.病人信息输入				*\n");
	printf("*                2.医生信息输入				*\n");
	printf("*                3.药品信息输入				*\n");
	printf("*********************************************************\n");
	printf("-------------------------------------------------------------\n");
	printf("请输入您所需要的选项：");
	while (~scanf("%d%*c", &ans))
		if (ans < 0 || ans > 3)
			printf("输入有误,请在1~3中进行选择:\n");
		else break;
	switch (ans) {
	case 1:
		head1 = input_patient(head1);	//病人数据输入 
		save_patient(head1);
		interface_admin();
		break;
	case 2:
		save_doctor(head3);
		inputdata_doc();             //医生数据输入的函数
		break;
	case 3:
		head2 = input_pharmaceuticals(head2);//药品输入 
		save_pharmaceuticals(head2);
		interface_admin();
		break;
	case 0:
		interface_admin();
		break;
	}
}
//ok
void look() { //显示界面
	system("cls");
	int ans;
		printf("欢迎进入显示界面(输入“0”返回主界面)	:			\n");
	printf("\n");
	printf("*********************************************************\n");
	printf("*                1.病人信息显示				*\n");
	printf("*                2.医生信息显示				*\n");
	printf("*                3.药品信息显示				*\n");
	printf("*********************************************************\n");
	printf("-------------------------------------------------------------\n");
	printf("请输入您所需要的选项：");
	while (~scanf("%d%*c", &ans))
		if (ans < 0 || ans > 3)
			printf("输入有误,请在0~3中进行选择:\n");
		else break;
	switch (ans) {
	case 1:
		system("cls");
		printf("\n\t\t\t☆☆☆显示病人数据(输1返回界面)☆☆☆\n");
		lookdata_pat(head1);//查看病人数据的函数
		break;
	case 2:
		lookdate_doc(head3);//查看医生数据
		break;
	case 3:
		lookdate_pha(head2);//查看药品数据
		break;
	case 0:
		interface_admin();
		break;
	}
}
//ok
void insert() { //插入界面
	system("cls");
	int ans;
	printf("欢迎进入插入界面(输入“0”返回主界面)	:			\n");
	printf("\n");
	printf("*********************************************************\n");
	printf("*                1.病人信息插入				*\n");
	printf("*                2.医生信息插入				*\n");
	printf("*                3.药品信息插入				*\n");
	printf("*********************************************************\n");
	printf("-------------------------------------------------------------\n");
	printf("请输入您所需要的选项：");
	while (~scanf("%d%*c", &ans))
		if (ans < 0 || ans > 3)
			printf("输入有误,请在0~3中进行选择:\n");
		else break;
	switch (ans) {
	case 1:
		add_pat(head1);          //插入病人数据
		break;
	case 2:
		insert_doctor(head3);    //插入医生数据
		break;
	case 3:
		add_pha(head2);          //插入药品数据
		break;
	case 0:
		interface_admin();
		break;
	}
}
//ok
void interface_delete() { //删除界面
	system("cls");
	int ans;
	printf("欢迎进入删除界面(输入“0”返回主界面)	:			\n");
	printf("\n");
	printf("*********************************************************\n");
	printf("*                1.病人信息删除				*\n");
	printf("*                2.医生信息删除				*\n");
	printf("*                3.药品信息删除				*\n");
	printf("*********************************************************\n");
	printf("-------------------------------------------------------------\n");
	printf("请输入您所需要的选项：");
	while (~scanf("%d%*c", &ans))
		if (ans < 0 || ans > 3)
			printf("输入有误,请在0~3中进行选择:\n");
		else break;
	switch (ans) {
	case 1:
		deleted_patient();        //删除病人数据
		break;
	case 2:
		deleted_doctor();         //删除医生信息
		break;
	case 3:
		deleted_pharmaceuticals();//删除药品信息
		break;
	case 0:
		interface_admin();
		break;
	}
}
//ok
void interface_look() { //查看
	system("cls");
	int ans;
	printf("欢迎进入查看界面(输入“0”返回主界面)	:			\n");
	printf("\n");
	printf("*********************************************************\n");
	printf("*                1.病人信息查看				*\n");
	printf("*                2.医生信息查看(按编号)			*\n");
	printf("*                3.医生信息查看(按科室)			*\n");
	printf("*                4.药品信息查看				*\n");
	printf("*                5.按病床查看病人			*\n");
	printf("*                6.按入院时间查看病人			*\n");
	printf("*                7.查看科室病人				*\n");
	printf("*********************************************************\n");
	printf("-------------------------------------------------------------\n");
	printf("请输入您所需要的选项：");
	while (~scanf("%d%*c", &ans))
		if (ans < 0 || ans > 7)
			printf("输入有误,请在0~7中进行选择:\n");
		else break;
	switch (ans) {
	case 1:
		system("cls");
		printf("\n\t\t\t☆☆☆显示病人数据(输入1返回界面)☆☆☆\n");
		lookdata_pat(head1);	//查看病人数据的函数
		break;
	case 2:
		system("cls");
		printf("\n\t\t\t☆☆☆查看数据(输入0返回界面)☆☆☆\n");
		find_ID_doc(head3);//按编号查看医生
		break;
	case 3:
		find_dep_doc(head3);//按科室查看医生
		//readdoc(head3);
		break;
	case 4:
		lookdate_pha(p2);  //药品信息
		//readpha(head2);
		break;
	case 5:
		system("cls");
		printf("\n\t\t\t☆☆☆查看数据(输入-1返回界面)☆☆☆\n");
		lookdata_pat(head1);
		find_bed(p1);    //按照床号寻找病人p1
		break;
	case 6:
		Sort(head1);       //排序
		break;
	case 7:
		find_depart(p1);  //按照科室查找病人p1
		lookdata_pat(head1);
		break;
	case 0:
		interface_admin();
		break;
	}
}
//ok
void revise_passward() { //密码修改界面
	system("cls");
	int ans;
	
		printf("欢迎进入修改界面(输入“0”返回主界面)	:			\n");
	printf("\n");
	printf("*********************************************************\n");
	printf("*                1.管理员密码修改			*\n");
	printf("*                2.医生密码修改				*\n");
	printf("*                3.病人密码修改				*\n");
	printf("*********************************************************\n");
	printf("-------------------------------------------------------------\n");
	printf("请输入您所需要的选项：");
	while (~scanf("%d%*c", &ans))
		if (ans < 0 || ans > 3)
			printf("输入有误,请在0~3中进行选择:\n");
		else break;
	switch (ans) {
	case 1:
		revise_admin();      //管理员账号,密码修改
		break;
	case 2:
		revise_doctor();      //病人账号，密码修改
		break;
	case 3:
		revise_user();        //病人账号，密码修改
		break;
	case 0:
		interface_admin();
		break;
	}
}
//ok 
pat* input_patient(pat* head1) { //输入病人相关数据p
	system("cls");
	struct patient* p = NULL; //要插入的新结点
	struct patient* q = NULL; 
	int a = 1;//判断是否结束 
	while (a != 0) {
		printf("如果结束录入工作，请输入0,否则输入1: \n");
		scanf("%d%*c", &a);
		p = (struct patient*)malloc(sizeof(struct patient)); //申请一个节点动态内存空间
		if (p == NULL) { //如果没有申请成功
			printf("No enough memory to allocate!\n");
			exit(0);
		}

		if (a == 0)
			break;

		printf("姓名:");
		scanf("%s%*c", p->name);
		printf("年龄:");
		scanf("%s%*c", p->year);
		printf("身份证号: ");
		scanf("%s%*c", p->ID);
		printf("性别:");
		scanf("%s%*c", p->sex);
		printf("入院时间：");
		scanf("%s%*c", p->time);
		printf("病症: ");
		scanf("%s%*c", p->disease);
		printf("科室:");
		scanf("%s%*c", p->department);
		printf("主治医生：");
		scanf("%s%*c", p->doctor);
		printf("手机号:");
		scanf("%s%*c", p->phone);
		printf("床号:");
		scanf("%s%*c", p->number);
		printf("家属手机号：");
		scanf("%s%*c", p->depend_phone);

		if (head1 == NULL) {//
			head1 = p;//head1指向p p值给head1 
			p->next = NULL;//链表尾  
		}
		else { //针对已有数据的链表需要检查是不是有该病人
			q = head1;
			while (strcmp(q->ID, p->ID) != 0 && q->next != NULL)//遍历 
				q = q->next;
			if (strcmp(q->ID, p->ID) == 0) {
				printf("\n\n\n\t很遗憾，你要录入的病人的姓名%s已经存在，无法录入！请重新输入\n\n\n", p->name);
			}
			else {
				p->next = head1;//head1值给p->next 
				head1 = p;      //head1空后 
			}
		}
	}
	//interface_admin();
	return (head1);
	
}
//ok 
pha* input_pharmaceuticals(pha* head2) { //输入药品
	system("cls");
	struct pharmaceuticals* p = NULL; //要插入的新结点
	struct pharmaceuticals* q = NULL; //
	printf("如果结束录入工作，请输入0,否则输入1：\n");
	int a = 1;
	while (a != 0) {
		scanf("%d", &a);
		p = (struct pharmaceuticals*)malloc(sizeof(struct pharmaceuticals)); //申请一个节点动态内存空间
		if (p == NULL) { //如果没有申请成功
			printf("No enough memory to allocate!\n");
			exit(0);
		}
		if (a == 0)
			break;
		printf("药品名称：\n");
		scanf("%s%*c", p->name);
		printf("药品价格：\n");
		scanf("%d%*c", &p->price);
		printf("药品生产公司：\n");
		scanf("%s%*c", p->origin);
		if (head2 == NULL) {
			head2 = p;
			p->next = NULL;
		}
		else { //针对已有数据的链表需要检查是不是有该病人
			q = head2;
			while (strcmp(q->name, p->name) != 0 && q->next != NULL)
				q = q->next;
			if (strcmp(q->name, p->name) == 0) {
				printf("\n\n\n\t很遗憾，你要录入的病人的姓名%s已经存在，无法录入！请重新输入\n\n\n", p->name);
			}
			else {
				p->next = head2;
				head2 = p;
			}
		}
	}
	return (head2);
}
//ok
doc* inputdata_doc() {   //医生数据输入的函数
	system("cls");
	struct doctor* p = NULL; //要插入的新结点
	struct doctor* q = NULL; //
	 
	int a = 1;
	while (a != 0)
	{
		printf("如果结束录入工作，请输入0,否则输入1：\n");
		scanf("%d", &a);
		p = (struct doctor*)malloc(sizeof(struct doctor)); //申请一个节点动态内存空间
		if (p == NULL) //如果没有申请成功
		{
			printf("No enough memory to allocate!\n");
			exit(0);
		}
		if (a == 0)
			//			break;
			interface_admin();
		printf("医生编号：\n");
		scanf("%s%*c", p->number);
		printf("医生姓名：\n");
		scanf("%s%*c", p->name);
		printf("所属科室：\n");
		scanf("%s%*c", p->department);
		printf("擅长病症：\n");
		scanf("%s%*c", p->excle);
		if (head3 == NULL)
		{
			head3 = p;
			p->next = NULL;
		}
		else //针对已有数据的链表需要检查是不是有该病人
		{
			q = head3;
			while (strcmp(q->number, p->number) != 0 && q->next != NULL)
				q = q->next;
			if (strcmp(q->number, p->number) == 0)
			{
				printf("\n\n\n\t很遗憾，你要录入的病人的姓名%s已经存在，无法录入！请重新输入\n\n\n", p->name);
			}
			else
			{
				p->next = head3;
				head3 = p;
			}
		}
	}
	//return (head3);
	interface_admin();
}
//ok
pat* adverse_reactions(pat* head1) { //输入不良反应
	system("cls");
	struct patient* p1 = head1;
	printf("\n\n\t请输入现象(如果结束录入工作，请输入0）：\n");
	int n = 1;
	char ID[20];
	printf("请输入身份证号：");
	scanf("%s", ID);
	while (strcmp(p1->ID, ID) != 0)
	{
		p1 = p1->next;
	}
	if (p1 != NULL)
	{
		printf("输入现象：\n");
		scanf("%s", p1->adverse_reactions);
	}
	scanf("%d%*c", &n);
	if (n == 0)
		interface_user();
	return p1;
}
//ok 
pat* pha_pat_doc(pat* head1) { //医生输入药品
	system("cls");
	struct patient* p1 = head1;
	printf("\n\n\t请输入病人所需药品(\n\n\t如果结束录入工作，请输入0）：\n");
	char ID[20];
	int i = 1;
	printf("请输入病人姓名：\n");
	scanf("%s", ID);
	while (strcmp(p1->ID, ID) != 0) {
		p1 = p1->next;
	}
	if (p1 != NULL) {
		scanf("%s", p1->pharmaceuticals);
	}
	scanf("%d%*c", &i);
	if (i == 0)
		interface_doctor();
	return (head1);
}
//ok 
pat* orders(pat* head1) { //输入医嘱
	system("cls");
	struct patient* p1 = head1;
	printf("\n\n\t请输入病人医嘱(如果结束录入工作，请输入0）：\n");
	int n = 1;
	char ID[20];
	printf("请输入身份证号：\n");
	scanf("%s", ID);
	while (strcmp(p1->ID, ID) != 0) {
		p1 = p1->next;
	}
	if (p1 != NULL) {
		printf("输入医嘱：\n");
		scanf("%s", p1->orders);
	}
	scanf("%d%*c", &n);
	if (n == 0)
		interface_doctor();
	return 0;
}
//ok
void revise_admin() { //管理员账号,密码修改
	system("cls");
	int a = 3, b = 3;
	//char account_admin[10] = "admin"; //管理员初始账号
	//char passward_admin[10] = "12345"; //管理员初始密码
	char  account[10] = { 0 };
	char passward[10] = { 0 };
	char passward1[10] = { 0 };
	char passward2[10] = { 0 };
	printf("\n\t\t\t☆☆☆管理员密码修改☆☆☆\n");
	while (a) {
		printf("请输入原有账号: \n");
		scanf("%s%*c", account);
		printf("请输入原有密码: \n");
		scanf("%s%*c", passward);
		if (strcmp(account, account_admin) == 0 && strcmp(passward, passward_admin) == 0) {
			while (b) {
				printf("请输入修改密码: \n");
				scanf("%s%*c", passward1);
				printf("请再次输入修改密码: \n");
				scanf("%s%*c", passward2);
				if (strcmp(passward1, passward2) == 0) {
					strcpy(passward_admin, passward1);
					//printf(passward_admin);
					printf("恭喜您，密码修改成功，请牢记新密码!\n");
					break;
				}
				else {
					b--;
					printf("账号或密码输入错误\n您还有%d次输入机会!\n", b);
				}
			}
			if (b == 0) {
				printf("您的输入机会已经用完\n,即将返回主界面!\n");
				Sleep(3000);
				revise_passward();
			}
			break;//改
		}
		else {
			a--;
			printf("账号或密码输入错误\n您还有%d次输入机会!\n", a);
		}
	}
	if (a == 0) {
		printf("您的输入机会已经用完\n,即将返回主界面!\n");
		Sleep(3000);
		revise_passward();
	}
	screen();
}
//ok
void revise_doctor() { //医生账号，密码修改
	system("cls");

	int a = 3, b = 3;
	char account_doctor[10] = "doctor";        //医生初始账号
	//char passward_doctor[10] = "12345"; //医生初始密码
	char  account[10] = { 0 };
	char passward[10] = { 0 };
	char passward1[10] = { 0 };
	char passward2[10] = { 0 };

	printf("\n\t\t\t☆☆☆医生密码修改☆☆☆\n");
	while (a) {
		printf("请输入原有账号: ");
		scanf("%s%*c", account);
		printf("请输入原有密码: ");
		scanf("%s%*c", passward);
		if (strcmp(account, account_doctor) == 0 && strcmp(passward, passward_doctor) == 0) {
			while (b) {
				printf("请输入修改密码: ");
				scanf("%s%*c", passward1);
				printf("请再次输入修改密码: ");
				scanf("%s%*c", passward2);
				if (strcmp(passward1, passward2) == 0) {
					strcpy(passward_doctor, passward1);
					printf("恭喜您，密码修改成功，请牢记新密码!\n");
					break;
				}
				else {
					b--;
					printf("账号或密码输入错误\n您还有%d次输入机会!\n", b);
				}
			}
			if (b == 0) {
				printf("您的输入机会已经用完\n,即将返回主界面!\n");
				Sleep(3000);
				revise_passward();
			}
			break;
		}
		else {
			a--;
			printf("账号或密码输入错误\n您还有%d次输入机会!\n", a);
		}
	}
	if (a == 0) {
		printf("您的输入机会已经用完\n,即将返回主界面!\n");
		Sleep(3000);
		revise_passward();
	}
	screen(); 
}
//ok
void revise_user() { //病人账号，密码修改
	system("cls");
	int a = 3, b = 3;
	//char account_user[10] = { "user" };  //用户初始账号
	//char passward_user[10] = { "12345" }; //用户初始密码
	char  account[10] = { 0 };
	char passward[10] = { 0 };
	char passward1[10] = { 0 };
	char passward2[10] = { 0 };

	printf("\n\t\t\t☆☆☆病人密码修改☆☆☆\n");
	while (a) {
		printf("请输入原有账号: ");
		scanf("%s%*c", account);
		printf("请输入原有密码: ");
		scanf("%s%*c", passward);
		if (strcmp(account, account_user) == 0 && strcmp(passward, passward_user) == 0) {
			while (b) {
				printf("请输入修改密码: ");
				scanf("%s%*c", passward1);
				printf("请再次输入修改密码：");
				scanf("%s%*c", passward2);
				if (strcmp(passward1, passward2) == 0) {
					strcpy(passward_user, passward1);
					printf("恭喜您，密码修改成功，请牢记新密码!\n");
					break;
				}
				else {
					b--;
					printf("账号或密码输入错误\n您还有%d次输入机会!\n", b);
				}
			}
			if (b == 0) {
				printf("您的输入机会已经用完\n,即将返回主界面!\n");
				Sleep(3000);
				revise_passward();
			}
			break;
		}
		else {
			a--;
			printf("账号或密码输入错误\n您还有%d次输入机会!\n", a);
		}
	}
	if (a == 0) {
		printf("您的输入机会已经用完\n,即将返回主界面!\n");
		Sleep(3000);
		revise_passward();
	}
}
//ok 
void add_pha(struct pharmaceuticals* head2) { //插入药品数据
	system("cls");
	struct pharmaceuticals* p = NULL, * p0 = NULL;  //定义p0为需增加的新节点
	char Name[20];
	int i = 1;
	p = head2;
	printf("请输入增加在哪个药品的后面(输入0返回界面)\n");
	scanf("%s%*c", Name);
	if (p != NULL) {
		p0 = (struct pharmaceuticals*)malloc(sizeof(struct pharmaceuticals));
		printf("药品名称：\n");
		scanf("%s%*c", p0->name);
		printf("药品价格：\n");
		scanf("%d%*c", &p0->price);
		printf("药品生产公司：\n");
		scanf("%s%*c", p0->origin);
		p0->next = p->next;
		p->next = p0;
		puts("插入成功!");
	}
	else
		printf("未找到该药品\n");
	printf("======================================================================\n");
	scanf("%d%*c", &i);
	if (i == 0)
		interface_admin();
}
//ok
void insert_doctor(struct doctor* head3) {	//医生信息插入 
	//插入医生数据
	system("cls");
	struct doctor* p = NULL, * p0 = NULL;
	char number[20];   //定义p0为需增加的新节点
	int i = 1;
	p = head3;
	printf("请输入增加在哪个医生的后面(输入0返回界面)\n");
	scanf("%s%*c", number);
	if (p != NULL) {
		p0 = (struct doctor*)malloc(sizeof(struct doctor));
		printf("医生编号：\n");
		scanf("%s%*c", p0->number);
		printf("医生姓名：\n");
		scanf("%s%*c", p0->name);
		printf("所属科室：\n");
		scanf("%s%*c", p0->department);;
		printf("擅长领域：\n");
		scanf("%s%*c", p0->excle);
		p0->next = p->next;
		p->next = p0;
		printf("插入成功!\n");
	}
	else
		printf("未找到该医生\n");
	printf("======================================================================\n");
	scanf("%d%*c", &i);
	if (i == 0)
		interface_admin();
}
//ok
void add_pat(struct patient* head1) { //插入病人数据
	system("cls");
	struct patient* p = NULL, * p0 = NULL;
	char ID[20];   //定义p0为需增加的新节点
	int i = 1;
	p = head1;
	printf("请输入增加在哪个病人的后面(输入0返回界面)\n");
	scanf("%s%*c", ID);
	if (p != NULL) {
		p0 = (struct patient*)malloc(sizeof(struct patient));
		printf("姓名:");
		scanf("%s%*c", p0->name);
		printf("年龄:");
		scanf("%s%*c", p0->year);
		printf("性别:");
		scanf("%s%*c", p0->sex);
		printf("入院时间：");
		scanf("%s%*c", p0->time);
		printf("病症: ");
		scanf("%s%*c", p0->disease);
		printf("科室:");
		scanf("%s%*c", p0->department);
		printf("主治医生：");
		scanf("%s%*c", p0->doctor);
		printf("手机号:");
		scanf("%s%*c", p0->phone);
		printf("床号:");
		scanf("%s%*c", p0->number);
		printf("家属手机号：");
		scanf("%s%*c", p0->depend_phone);
		printf("药品:");
		scanf("%s%*c", p0->pharmaceuticals);
		p0->next = p->next;
		p->next = p0;
		printf("插入成功!\n");
		printf("======================================================================\n");
	}
	else
		printf("未找到该病人\n");
	scanf("%d%*c", &i);
	if (i == 0)
		interface_admin();
}
//ok
pat* lookdata_pat(pat* p1) { //查看病人数据的函数
	int i = 2;
	printf("----------------------------------------------------------------------\n");
	while (p1 != NULL) {
		printf("姓名:%s\n", p1->name);
		printf("性别:%s\n", p1->sex);
		printf("年龄:%s\n", p1->year);
		printf("身份证号:%s\n", p1->ID);
		printf("入院时间:%s\n", p1->time);
		printf("病症:%s\n", p1->disease);
		printf("付费方式:%s\n", p1->pay);
		printf("科室:%s\n", p1->department);
		printf("主治医生：%s\n", p1->doctor);
		printf("手机号：%s\n", p1->phone);
		printf("床号：%s\n", p1->number);
		printf("医嘱：%s\n", p1->orders);
		printf("家属：%s\n", p1->dependents);
		printf("家属联系方式：%s\n", p1->depend_phone);
		printf("药品：%s\n", p1->pharmaceuticals);
		printf("不良反应：%s\n", p1->adverse_reactions); //
		printf("======================================================================\n");
		p1 = p1->next;
	}
	scanf("%d%*c", &i);
	switch (i) {
	case 1:
		interface_admin();
		break;
	case 0:
		interface_doctor();//返回医生
		break;
	}
	return p1;
}
//ok
pha* lookdate_pha(pha* p2) { //查看药品数据的函数p2
	system("cls");
	int i = 1;

	printf("\n\t\t\t☆☆☆显示药品数据☆☆☆\n");
	printf("输0返回界面\n");
	printf("----------------------------------------------------------------------\n");
	while (p2 != NULL) {
		printf("药品名称:%s\n", p2->name);
		printf("药品单价:%d\n", p2->price);
		printf("药品产地:%s\n", p2->origin);
		printf("======================================================================\n");
		p2 = p2->next;
	}
	scanf("%d%*c", &i);
	if (i == 0)
		interface_admin();;
	return p2;
}
//ok 
pat* look_pat_pha(pat* p1) { //查看病人药品
	system("cls");
	p1 = head1;
	int i = 1;

	printf("\n\t\t\t☆☆☆显示病人药品☆☆☆\n");
	printf("输0返回界面\n");
	printf("----------------------------------------------------------------------\n");
	if (head1 != NULL) {
		while (p1 != NULL) {
			printf("病人床号：%s\n", p1->number);
			printf("病人姓名：%s\n", p1->name);
			printf("病人身份证号：%s\n", p1->ID);
			printf("药品：%s\n", p1->pharmaceuticals);
			printf("======================================================================\n");
			p1 = p1->next;
		}
	}
	scanf("%d%*c", &i);
	if (i == 0)
		interface_user();
	return p1;
}
//ok 
void update_pha_pat(pat* p1) {  //查找病人修改药品数据
	char ID[20];
	int b = 0, i = 1;
	printf("\n\t\t\t☆☆☆修改数据☆☆☆\n");
	printf("----------------------------------------------------------------------\n");
	printf("请输入将要修改人的身份证号:");
	scanf("%s%*c", ID);
	while (p1 != NULL) {
		if (strcmp(ID, p1->ID) == 0) {
			printf("该病人药品的基本信息\n");
			printf("药品：%s\n", p1->pharmaceuticals);
			printf("修改药品：\n");
			scanf("%s%*c", p1->pharmaceuticals);
			printf("\n修改成功!\n");
			printf("=========================================================================\n");
			b = 1;
		}
		p1 = p1->next;
	}
	if (b == 0) {
		printf("没有找到该人的资料!\n");
	}
	scanf("%d%*c", &i);
	if (i == 0)
		interface_doctor();
}
//ok
doc* lookdate_doc(doc* p3) { //查看医生数据的函数p3
	system("cls");
	int i = 1;

	printf("\n\t\t\t☆☆☆显示医生数据☆☆☆\n");
	printf("输0返回界面\n");
	printf("----------------------------------------------------------------------\n");
	while (p3 != NULL) {
		printf("医生编号:%s\n", p3->number);
		printf("医生姓名:%s\n", p3->name);
		printf("所属科室:%s\n", p3->department);
		printf("医生擅长病症:%s\n", p3->excle);
		printf("======================================================================\n");
		p3 = p3->next;
	}
	scanf("%d%*c", &i);
	if (i == 0)
		interface_admin();
	return p3;
}
//ok
pat* lookdate_reactions(pat* p1) { //查看不良反应
	system("cls");
	p1 = head1;
	int i = 1;
	printf("\n\t\t\t☆☆☆显示病人不良反应☆☆☆\n");
	printf("输入0返回界面\n");
	printf("----------------------------------------------------------------------\n");
	if (head1 != NULL) {
		while (p1 != NULL) {
			printf("病人床号：%s\n", p1->number);
			printf("病人姓名：%s\n", p1->name);
			printf("病人身份证号：%s\n", p1->ID);
			printf("现象：%s\n", p1->adverse_reactions);
			printf("======================================================================\n");
			p1 = p1->next;
		}
	}
	scanf("%d%*c", &i);
	if (i == 0)
		interface_doctor();
	return p1;
}
//ok 
pat* lookdate_orders(pat* p1) { //查看医嘱
	system("cls");
	p1 = head1;
	int i = 1;
	printf("\n\t\t\t☆☆☆显示医嘱（输0返回界面）☆☆☆\n");
	printf("----------------------------------------------------------------------\n");
	if (head1 != NULL) {
		while (p1 != NULL) {
			printf("病人床号：%s\n", p1->number);
			printf("病人姓名：%s\n", p1->name);
			printf("病人身份证号：%s\n", p1->ID);
			printf("医嘱：%s\n", p1->orders);
			printf("======================================================================\n");
			p1 = p1->next;
		}
	}
	scanf("%d%*c", &i);
	if (i == 0)
		interface_user();
	return p1;
}
//ok
void deleted_patient() { //删除病人数据
	system("cls");
	pat* q1 = NULL;
	pat* q2 = NULL;
	char ID[20];
	int i = 1;
	printf("\n\t\t\t☆☆☆删除数据（输0返回界面）☆☆☆\n");
	printf("----------------------------------------------------------------------\n");
	printf("请输入要删除的病人身份证号:");
	scanf("%s%*c", ID);
	q1 = head1;//指向 
	if (head1 == NULL) {//未录入 
		printf("查无此人\n");
		printf("======================================================================\n");
		scanf("%d%*c", &i);
		if (i == 0)
			interface_delete();
		return;
	}
	if (strcmp(ID, q1->ID) == 0) {
		head1 = q1->next;//删q1 
		printf("删除成功!\n");
		printf("======================================================================\n");
		scanf("%d%*c", &i);
		if (i == 0)
			interface_delete();
		return;
	}
	while (q1 != NULL && (strcmp(ID, q1->ID) != 0)) {
		q2 = q1;//?
		q1 = q1->next;//遍历q1的ID （改变q1） 
	}
	if (q1 == NULL) {
		printf("查无此人!\n");
		printf("======================================================================\n");
		scanf("%d%*c", &i);
		if (i == 0)
			interface_delete();
		return;
	}
	if (q1->next != NULL) { //
		q1 = q1->next;
		q2->next = q1;
		printf("删除成功!\n");
		printf("======================================================================\n");
		scanf("%d%*c", &i);
		if (i == 0)
			interface_delete();
		return;
	}
	else { //最后
		q2->next = NULL;
		printf("删除成功!\n");
		printf("======================================================================\n");
		scanf("%d%*c", &i);
		if (i == 0)
			interface_delete();
		return;
	}
}
//ok
void deleted_doctor() { //删除医生数据
	system("cls");
	doc* q1, * q2;
	int i = 1;
	char number[20];  //想要删除的人的姓名
	printf("\n\t\t\t☆☆☆删除数据☆☆☆\n");
	printf("输0返回界面\n");
	printf("----------------------------------------------------------------------\n");
	printf("请输入要删除的编号:");
	scanf("%s", number);
	q1 = head3;
	q2 = head3;
	if (head3 == NULL) {
		printf("查无此人\n");
		printf("======================================================================\n");
		scanf("%d%*c", &i);
		if (i == 0)
			interface_delete();
		return;
	}
	if (strcmp(number, q1->number) == 0) {
		head3 = q1->next;
		printf("删除成功!\n");
		printf("======================================================================\n");
		scanf("%d%*c", &i);
		if (i == 0)
			interface_delete();
		return;
	}
	while (q1 != NULL && (strcmp(number, q1->number) != 0)) {
		q2 = q1;
		q1 = q1->next;
	}
	if (q1 == NULL) {
		printf("查无此人\n");
		printf("======================================================================\n");
		scanf("%d%*c", &i);
		if (i == 0)
			interface_delete();
		return;
	}
	if (q1->next != NULL) {
		q1 = q1->next;
		q2->next = q1;
		printf("删除成功!\n");
		printf("======================================================================\n");
		scanf("%d%*c", &i);
		if (i == 0)
			interface_doctor();
		return;
	}
	else {
		q2->next = NULL;
		printf("删除成功!\n");
		printf("======================================================================\n");
		scanf("%d%*c", &i);
		if (i == 0)
			interface_delete();
		return;
	}
	save_doctor(head3);
}
//ok
void deleted_pharmaceuticals() { //删除药品数据
	system("cls");
	pha* q1, * q2;
	char Name[20];               //想要删除的人的姓名
	int i = 1;
	printf("\n\t\t\t☆☆☆删除数据☆☆☆\n");
	printf("返回界面请输0\n");
	printf("----------------------------------------------------------------------\n");
	printf("请输入要删除的名称:");
	scanf("%s", Name);
	q1 = head2;
	q2 = head2;
	if (head2 == NULL) {
		printf("查无此药\n");
		printf("======================================================================\n");
		scanf("%d%*c", &i);
		if (i == 0)
			interface_delete();
		return;
	}
	else if (strcmp(Name, q1->name) == 0) {
		head2 = q1->next;
		printf("删除成功!\n");
		printf("======================================================================\n");
		scanf("%d%*c", &i);
		if (i == 0)
			interface_delete();
		return;
	}
	while (q1 != NULL && (strcmp(Name, q1->name) != 0)) {
		q2 = q1;
		q1 = q1->next;
	}
	if (q1 == NULL) {
		printf("查无此药\n");
		printf("======================================================================\n");
		scanf("%d%*c", &i);
		if (i == 0)
			interface_delete();
		return;
	}
	else if (q1->next != NULL) {
		q1 = q1->next;
		q2->next = q1;
		printf("删除成功!\n");
		printf("======================================================================\n");
		scanf("%d%*c", &i);
		if (i == 0)
			interface_delete();
		return;
	}
	else {
		q2->next = NULL;
		printf("删除成功!\n");
		printf("======================================================================\n");
		scanf("%d%*c", &i);
		if (i == 0)
			interface_delete();
		return;
	}
}
//ok
void find_ID(pat* p1) { //p1       //通过身份证号查找查看数据的函数
	char ID[20];
	int b = 0;
	int i = 5;
	printf("----------------------------------------------------------------------\n");
	printf("请输入您想查找人的身份证号:");
	scanf("%s%*c", ID);
	while (p1 != NULL) {
		if (strcmp(ID, p1->ID) == 0) {
			printf("你要找到的数据\n");
			printf("姓名:%s\n", p1->name);
			printf("性别:%s\n", p1->sex);
			printf("年龄:%s\n", p1->year);
			printf("身份证号:%s\n", p1->ID);
			printf("入院时间:%s\n", p1->time);
			printf("病症:%s\n", p1->disease);
			printf("付费方式:%s\n", p1->pay);
			printf("科室:%s\n", p1->department);
			printf("主治医生：%s\n", p1->doctor);
			printf("手机号：%s\n", p1->phone);
			printf("床号：%s\n", p1->number);
			printf("医嘱：%s\n", p1->orders);
			printf("家属：%s\n", p1->dependents);
			printf("家属联系方式：%s\n", p1->depend_phone);
			printf("药品：%s\n", p1->pharmaceuticals);
			printf("======================================================================\n");
			b = 1;
		}
		p1 = p1->next;
	}
	if (b == 0) {
		printf("\n您要查找的人不存在!\n");
	}
	scanf("%d%*c", &i);
	if (i == 0) {
		interface_doctor();
	}
}
//ok
void find_ID_doc(doc* p3) { //p1       //通过编号查找医生数据的函数
	char number[20];
	int b = 0;
	printf("----------------------------------------------------------------------\n");
	printf("请输入您想查找医生的编号:");
	scanf("%s%*c", number);
	while (p3 != NULL) {
		if (strcmp(number, p3->number) == 0) {
			printf("你要找到的数据\n");
			printf("姓名:%s\n", p3->number);
			printf("性别:%s\n", p3->name);
			printf("年龄:%s\n", p3->department);
			printf("身份证号:%s\n", p3->excle);
			printf("======================================================================\n");
			b = 1;
		}
		p1 = p1->next;
	}
	if (b == 0) {
		printf("\n您要查找的人不存在!\n");
	}
	int i = 0;
	scanf("%d", &i);
	if (i == 0)
		interface_look();
	if (i == 1)
		interface_user();
}
//ok
void find_dep_doc(doc* p3) { //p1       //通过科室查找医生数据的函数
	system("cls");
	char dep[20];
	int b = 0;
	printf("\n\t\t\t☆☆☆查看数据☆☆☆\n");
	printf("输0返回界面\n");
	printf("----------------------------------------------------------------------\n");
	printf("请输入您想查找医生的科室:");
	scanf("%s%*c", dep);
	while (p3 != NULL) {
		if (strcmp(dep, p3->department) == 0) {
			printf("你要找到的数据\n");
			printf("姓名:%s\n", p3->number);
			printf("性别:%s\n", p3->name);
			printf("年龄:%s\n", p3->department);
			printf("身份证号:%s\n", p3->excle);
			printf("======================================================================\n");
			b = 1;
		}
		p1 = p1->next;
	}
	if (b == 0) {
		printf("\n您要查找的人不存在!\n");
	}
	int i = 2;
	scanf("%d", &i);
	if (i == 0)
		interface_look();
}
//ok
void find_depart(pat* p1) { //按照科室查找病人p1
	system("cls");
	char department[20];
	int b = 0;
	int i = 1;
	printf("\n\t\t\t☆☆☆查看数据☆☆☆\n");
	printf("返回界面请输0\n");
	printf("----------------------------------------------------------------------\n");
	printf("请输入您想查找的科室:");
	scanf("%s%*c", department);
	while (p1 != NULL) {
		if (strcmp(department, p1->department) == 0) {
			printf("你要找到的数据\n");
			printf("姓名:%s\n", p1->name);
			printf("性别:%s\n", p1->sex);
			printf("年龄:%s\n", p1->year);
			printf("身份证号:%s\n", p1->ID);
			printf("入院时间:%s\n", p1->time);
			printf("病症:%s\n", p1->disease);
			printf("付费方式:%s\n", p1->pay);
			printf("科室:%s\n", p1->department);
			printf("主治医生：%s\n", p1->doctor);
			printf("手机号：%s\n", p1->phone);
			printf("床号：%s\n", p1->number);
			printf("医嘱：%s\n", p1->orders);
			printf("家属：%s\n", p1->dependents);
			printf("家属联系方式：%s\n", p1->depend_phone);
			printf("药品：%s\n", p1->pharmaceuticals);
			printf("======================================================================\n");
			b = 1;
		}
		p1 = p1->next;
	}
	if (b == 0) {
		printf("\n您要查找的人不存在!\n");
	}
	scanf("%d%*c", &i);
	if (i == 0)
		interface_doctor();
}
//ok
void find_bed(pat* p1) { //按照床号寻找病人p1
	char bed[20];
	int b = 0;
	int i = 5;
	printf("----------------------------------------------------------------------\n");
	printf("请输入您想查找人的病床号:");
	scanf("%s", bed);
	while (p1 != NULL) {
		if (strcmp(bed, p1->number) == 0) {
			printf("你要找到的数据\n");
			printf("姓名:%s\n", p1->name);
			printf("性别:%s\n", p1->sex);
			printf("年龄:%s\n", p1->year);
			printf("身份证号:%s\n", p1->ID);
			printf("入院时间:%s\n", p1->time);
			printf("病症:%s\n", p1->disease);
			printf("付费方式:%s\n", p1->pay);
			printf("科室:%s\n", p1->department);
			printf("主治医生：%s\n", p1->doctor);
			printf("手机号：%s\n", p1->phone);
			printf("床号：%s\n", p1->number);
			printf("医嘱：%s\n", p1->orders);
			printf("家属：%s\n", p1->dependents);
			printf("家属联系方式：%s\n", p1->depend_phone);
			printf("药品：%s\n", p1->pharmaceuticals);
			printf("======================================================================\n");
			b = 1;
		}
		p1 = p1->next;
	}
	if (b == 0) {
		printf("\n您要查找的人不存在!\n");
	}
	scanf("%d%*c", &i);
	if (i == 0)
		interface_user();
	if (i == 1)
		interface_doctor();
	if (i == -1)
		interface_look();
}
//ok
void update_patient(pat* p1) { //通过身份证号查找修改数据p1
	system("cls");

	char ID[20];
	int b = 0, i;
	printf("\n\t\t\t☆☆☆修改数据(输0返回界面)☆☆☆\n");
	printf("----------------------------------------------------------------------\n");
	printf("请输入将要修改人的身份证号:");
	scanf("%s%*c", ID);
	while (p1 != NULL) {
		if (strcmp(ID, p1->ID) == 0) {
			printf("该病人的基本信息\n");
			printf("姓名:%s\n", p1->name);
			printf("性别:%s\n", p1->sex);
			printf("年龄:%s\n", p1->year);
			printf("身份证号:%s\n", p1->ID);
			printf("入院时间:%s\n", p1->time);
			printf("病症:%s\n", p1->disease);
			printf("付费方式:%s\n", p1->pay);
			printf("科室:%s\n", p1->department);
			printf("主治医生：%s\n", p1->doctor);
			printf("手机号：%s\n", p1->phone);
			printf("床号：%s\n", p1->number);
			printf("医嘱：%s\n", p1->orders);
			printf("家属：%s\n", p1->dependents);
			printf("家属联系方式：%s\n", p1->depend_phone);
			printf("药品：%s\n", p1->pharmaceuticals);
			printf("\n请选择要修改的信息\n");
			printf("\t1.姓名\t2.性别\t3.年龄\t4.身份证号\t5.入院时间\n\n\t6.病症\t7.付费方式\t8.科室\t9.主治医生\t10.手机号\n\n\t11.病床号\t12.医嘱\t13.家属\t14.家属联系方式\t15.药品\n");
			printf("\n您的选择是(1~15):");
			scanf("%d", &i);
			printf("请输入修改之后的内容\n");
			switch (i) {
			case 1:
				printf("姓名:\n");
				scanf("%s%*c", p1->name);
				break;
			case 2:
				printf("性别:\n");
				scanf("%s%*c", p1->sex);
				break;
			case 3:
				printf("年龄:\n");
				scanf("%s%*c", p1->year);
				break;
			case 4:
				printf("身份证号:\n");
				scanf("%s%*c", p1->ID);
				break;
			case 5:
				printf("入院时间:\n");
				scanf("%s%*c", p1->time);
				break;
			case 6:
				printf("病症:\n");
				scanf("%s%*c", p1->disease);
				break;
			case 7:
				printf("付费方式:\n");
				scanf("%s%*c", p1->pay);
				break;
			case 8:
				printf("科室:\n");
				scanf("%s%*c", p1->department);
				break;
			case 9:
				printf("主治医生：\n");
				scanf("%s%*c", p1->doctor);
				break;
			case 10:
				printf("手机号：\n");
				scanf("%s%*c", p1->phone);
				break;
			case 11:
				printf("床号：\n");
				scanf("%s%*c", p1->number);
				break;
			case 12:
				printf("医嘱：\n");
				scanf("%s%*c", p1->orders);
				break;
			case 13:
				printf("家属：\n");
				scanf("%s%*c", p1->dependents);
				break;
			case 14:
				printf("家属联系方式：\n");
				scanf("%s%*c", p1->depend_phone);
				break;
			case 15:
				printf("药品：\n");
				scanf("%s%*c", p1->pharmaceuticals);
				break;
			}
			printf("\n修改成功!\n");
			printf("=========================================================================\n");
			b = 1;
		}
		p1 = p1->next;
	}
	if (b == 0) {
		printf("没有找到该人的资料!\n");
	}
	scanf("%d%*c", &i);
	if (i == 0)
		interface_admin();
}
//ok
void update_doctor(doc* p3) { //查找医生修改数据p3
	system("cls");
	char number[20];
	int b = 0, i;
	printf("\n\t\t\t☆☆☆修改数据(输0返回界面)☆☆☆\n");
	printf("----------------------------------------------------------------------\n");
	printf("请输入将要修改人的姓名:");
	scanf("%s", number);
	while (p3 != NULL) {
		if (strcmp(number, p3->number) == 0) {
			printf("该医生的基本信息\n");
			printf("医生编号:%s\n", p3->number);
			printf("医生姓名:%s\n", p3->name);
			printf("医生擅长病症:%s\n", p3->excle);
			printf("所属科室:%s\n", p3->department);
			printf("\n请选择要修改的信息\n");
			printf("\t1.编号\t2.姓名\t3.擅长病症\n4.所属科室");
			printf("\n您的选择是(1~4):");
			scanf("%d", &i);
			printf("请输入修改之后的内容\n");
			switch (i) {
			case 1:
				printf("编号:");
				scanf("%s%*c", p3->number);
				break;
			case 2:
				printf("姓名:");
				scanf("%s%*c", p3->name);
				break;
			case 3:
				printf("擅长病症:");
				scanf("%s%*c", p3->excle);
				break;
			case 4:
				printf("所属科室:");
				scanf("%s%*c", p3->department);
				break;
			}
			printf("\n修改成功!\n");
			printf("=========================================================================\n");
			b = 1;
		}
		p3 = p3->next;
	}
	if (b == 0) {
		printf("没有找到该人的资料!\n");
	}
	scanf("%d%*c", &i);
	if (i == 0)
		interface_admin();
}
//ok
void update_pharmaceuticals(pha* p2) { //查找药品修改数据p2
	system("cls");
	char name[20];
	int b = 0, i;
	printf("\n\t\t\t☆☆☆修改数据☆☆☆\n");
	printf("输0返回界面\n");
	printf("----------------------------------------------------------------------\n");
	printf("请输入将要修改药品名称:");
	scanf("%s", name);
	while (p2 != NULL) {
		if (strcmp(name, p2->name) == 0) {
			printf("该药品的基本信息\n");
			printf("药品名称:%s\n", p2->name);
			printf("药品单价:%d\n", p2->price);
			printf("药品产地:%s\n", p2->origin);
			printf("\n请选择要修改的信息\n");
			printf("\t1.药品名称\t2.药品单价\t3.药品产地\n");
			printf("\n您的选择是(1~3):");
			scanf("%d", &i);
			printf("请输入修改之后的内容\n");
			switch (i) {
			case 1:
				printf("药品名称:");
				scanf("%s%*c", p2->name);
				break;
			case 2:
				printf("药品单价:");
				scanf("%d%*c", &p2->price);
				break;
			case 3:
				printf("药品产地:");
				scanf("%s%*c", p2->origin);
				break;
			}
			printf("\n修改成功!\n");
			printf("=========================================================================\n");
			b = 1;
		}
		p2 = p2->next;
	}
	if (b == 0) {
		printf("没有找到该药品的资料!\n");
	}
	scanf("%d%*c", &i);
	if (i == 0)
		interface_admin();
}
//ok
void* Sort(struct patient* head1) { //排序
	system("cls");
	int choose;
	char temp[20];
	struct patient* p = NULL; //相当于数组排序中的i
	struct patient* q = NULL; //相当于数组排序中的j
	struct patient* k = NULL; //相当于数组排序中的k

	printf("降序请按1，升序请按2");
	scanf("%d%*c", &choose);
	if (head1 != NULL) {
		for (p = head1; p != NULL; p = p->next) { //相当于数组排序中的for(i=0;i<n-1;i++)
			k = p; //相当于数组排序中的k=i(给标准)
			for (q = p->next; q != NULL; q = q->next) {
				//相当于数组排序中的for(j=i+1;j<n;j++)
				if (strcmp(q->time, k->time) > 0 && choose == 1) //降序（后面的大则记录下来，即让k指向这个大的节点）
					k = q;
				else if (strcmp(q->time, k->time) < 0 && choose == 2) //升序（后面的小则记录下来，即让k指向这个小的节点）
					k = q;
			}
			if (k != p) { //交换数据
				strcpy(temp, p->name);
				strcpy(p->name, k->name);
				strcpy(k->name, temp);

				strcpy(temp, p->sex);
				strcpy(p->sex, k->sex);
				strcpy(k->sex, temp);

				strcpy(temp, p->year);
				strcpy(p->year, k->year);
				strcpy(k->year, temp);

				strcpy(temp, p->ID);
				strcpy(p->ID, k->ID);
				strcpy(k->ID, temp);

				strcpy(temp, p->time);
				strcpy(p->time, k->time);
				strcpy(k->time, temp);

				strcpy(temp, p->disease);
				strcpy(p->disease, k->disease);
				strcpy(k->disease, temp);

				strcpy(temp, p->pay);
				strcpy(p->pay, k->pay);
				strcpy(k->pay, temp);

				strcpy(temp, p->department);
				strcpy(p->department, k->department);
				strcpy(k->department, temp);

				strcpy(temp, p->doctor);
				strcpy(p->doctor, k->doctor);
				strcpy(k->doctor, temp);

				strcpy(temp, p->phone);
				strcpy(p->phone, k->phone);
				strcpy(k->phone, temp);

				strcpy(temp, p->number);
				strcpy(p->number, k->number);
				strcpy(k->number, temp);

				strcpy(temp, p->orders);
				strcpy(p->orders, k->orders);
				strcpy(k->orders, temp);

				strcpy(temp, p->dependents);
				strcpy(p->dependents, k->dependents);
				strcpy(k->dependents, temp);

				strcpy(temp, p->depend_phone);
				strcpy(p->depend_phone, k->depend_phone);
				strcpy(k->depend_phone, temp);

				strcpy(temp, p->pharmaceuticals);
				strcpy(p->pharmaceuticals, k->pharmaceuticals);
				strcpy(k->pharmaceuticals, temp);

				strcpy(temp, p->adverse_reactions);
				strcpy(p->adverse_reactions, k->adverse_reactions);
				strcpy(k->adverse_reactions, temp);
			}
		}
	}
	else
		printf("\n\n\t抱歉，没有病人数据！\n\n");
	lookdata_pat(head1);
	Sleep(3000);
	interface_admin();
	return (head1);
}
//ok
void save_patient(pat* head1) { //病人文件写入 
    FILE *fp;
    struct patient *p = head1;

    if (head1 == NULL) {
        printf("\t暂无病人信息\n");
        return;
    }

    if ((fp = fopen("data/病人信息.txt", "w")) == NULL) { 
        perror("\t打开文件失败！");
        return;
    }

    while (p != NULL) {
        if (fprintf(fp, "%s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s\n",
                p->name, p->sex, p->year, p->ID, p->time,
                p->disease, p->pay, p->department, p->doctor,
                p->phone, p->number, p->orders, p->dependents,
                p->depend_phone, p->pharmaceuticals, p->adverse_reactions) < 0) {
            perror("写入文件失败！");
            fclose(fp);
            return;
        }
        p = p->next;
    }
    fclose(fp);
}
//ok
void save_doctor(doc* head3) { //医生文件写入 
    FILE *fp;
    struct doctor *p = head3;

    if (head3 == NULL) {
        printf("\t暂无医生信息\n");
        return;
    }

    if ((fp = fopen("data/医生信息.txt", "w")) == NULL) { 
        perror("\t打开文件失败！");
        return;
    }

    while (p != NULL) {
        if (fprintf(fp, "%s %s %s %s\n", p->number, p->name, p->excle, p->department) < 0) {
            perror("写入文件失败！");
            fclose(fp);
            return;
        }
        p = p->next;
    }
    fclose(fp);
}
//ok
void save_pharmaceuticals(pha* head2) { //药品文件写入 
    FILE *fp;
    struct pharmaceuticals *p = head2;
    if (head2 == NULL) {
        printf("\t暂无药品信息\n");
        return;
    }
    if ((fp = fopen("data/药品信息.txt", "w")) == NULL) { // 打开文本文件用于写入
        perror("\t打开文件失败！\n");
        return;
    }
    while (p != NULL) { // 将链表数据写入文件
        fprintf(fp, "%s\n%d\n%s\n%s\n", p->name, p->price, p->origin, p->money);
        p = p->next;
    }
    fclose(fp); // 关闭文件
}

//ok
struct patient* readpat(struct patient* head1) { // 病人信息读取 
    FILE *fp;
    struct patient *new_node = NULL;

    if ((fp = fopen("data/病人信息.txt", "r")) == NULL) { 
        perror("\t打开文件失败！");
        return head1;
    }

    while (!feof(fp)) {
        new_node = (struct patient *)malloc(sizeof(struct patient));
        if (new_node == NULL) {
            perror("Memory allocation failed");
            fclose(fp);
            return head1;
        }

        // 读取数据
        if (fscanf(fp, "%s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s",
                new_node->name, new_node->sex, new_node->year, new_node->ID, new_node->time,
                new_node->disease, new_node->pay, new_node->department, new_node->doctor,
                new_node->phone, new_node->number, new_node->orders, new_node->dependents,
                new_node->depend_phone, new_node->pharmaceuticals, new_node->adverse_reactions) != 16) {
            // 检查是否读取成功（16个字段）
            perror("读取数据失败");
            free(new_node);
            break; // 停止读取
        }

        new_node->next = head1;
        head1 = new_node;
    }

    fclose(fp);
    return head1;
}

//ok
struct doctor* readdoc(struct doctor* head3) { // 医生信息读取 
    FILE *fp;
    struct doctor *p = NULL;
    struct doctor *new_node = NULL;

    if ((fp = fopen("data/医生信息.txt", "r")) == NULL) { 
        perror("\t打开文件失败！");
        return head3;
    }

    while (!feof(fp)) {
        new_node = (struct doctor *)malloc(sizeof(struct doctor));
        if (new_node == NULL) {
            perror("Memory allocation failed");
            fclose(fp);
            return head3;
        }

        // 读取数据
        if (fscanf(fp, "%s %s %s %s",
                new_node->number, new_node->name, new_node->excle, new_node->department) != 4) {
            // 检查是否读取成功（4个字段）
            perror("读取数据失败");
            free(new_node);
            break; // 停止读取
        }

        new_node->next = head3;
        head3 = new_node;
    }

    fclose(fp);
    return head3;
}

//ok 
struct pharmaceuticals* readpha(struct pharmaceuticals* head2) { // 药品信息读取 
    FILE *fp;
    struct pharmaceuticals *new_node = NULL;

    if ((fp = fopen("data/药品信息.txt", "r")) == NULL) { 
        perror("\t打开文件失败！");
        return head2;
    }

    while (!feof(fp)) {
        new_node = (struct pharmaceuticals *)malloc(sizeof(struct pharmaceuticals));
        if (new_node == NULL) {
            perror("Memory allocation failed");
            fclose(fp);
            return head2;
        }

        // 读取数据
        if (fscanf(fp, "%s %d %s %s",
                new_node->name, &new_node->price, new_node->origin, new_node->money) != 4) {
            // 检查是否读取成功（4个字段）
            perror("读取数据失败");
            free(new_node);
            break; // 停止读取
        }

        new_node->next = head2;
        head2 = new_node;
    }

    fclose(fp);
    return head2;
}

