//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myfile.h"

int main(void) 
{
	//函数调用变量
	int bool_judge = 0;
	int ret = 0;
	int result = 0;
	//管理客房使用变量
	int date_check_in = 0;
	int date_check_out = 0;
	//main函数使用变量
	char user_name[16];
	char user_passwd[16];
	room *room_head = NULL;
	user *user_head = NULL;
	//开始界面
	int m = 1; 
	int n = 1;
	int chose = 1;
	int i = 0;
	user *user_id = NULL;
	int id = 0;
	//程序数据载入
	load_userdata(&user_head);
	ret = 0;
	load_roomdata(&room_head, &ret);
	printf("--------welcome to the hotel management system--------\n");
	while (m){
	printf("1.register \n2.login \nother.exit \nenter :");
	scanf("%d",&chose);
	printf("\n");
	//重复校验用户信息
		switch(chose) {
			case 1:
				//用户注册 
				while(n){
					printf("enter a new user name:");
					gets(user_name);
					printf("enter passwd:");
					gets(user_passwd);
					ret = user_register(user_head, user_name, user_passwd, &bool_judge);
					if (ret != 0){
						printf("非法传参数\n");
						return -1;
					}
					if (bool_judge == 1){
					 	printf("err:registered fail,user-name has registered\n");
					 	printf("continue register, please input 1,other input will exit\n");
					 	scanf("%d",&i);
						//退出死循环 
					 	if(i != 1){
					 		n = 0;
						 }
						continue;
					 }
				}
				break;
			case 2:
				//用户登录 
				while(n){ 
					printf("login name:");
					gets(user_name);
					printf("passwd:");
					gets(user_passwd);
					check_user_login(user_name, user_passwd, &bool_judge, user_head, &user_id);
					if(bool_judge == -1){
						printf("err:user do not available,please input again\n");
						printf("continue login please input 1,other input will exit:");
						scanf("%d",&i);
						if(i != 1){
						 	//退出死循环 
							break;
			    		 }
						continue;
					}
					else if (bool_judge == -2){
						printf("err:user password incorrect\n");
					}else{
						m = 0;
						break;
						//退出死循环 
					}
				} 
				break;
			default:
				//退出 
				break;
				return 0;
		}
    }
	//初始化辅助变量
	i = 0; chose = 0;
	m = 0; n = 0;
	//管理界面
	if (user_id == NULL){
		printf("user do not login success\n");
		return -1;
	}
	system("cls");
	printf("---%s-----welcome to the hotel management system--------\n",user_id->name);
	m = 1;
	while (m){
		printf("----------------------please input sums to chose\n----------------\n");
		printf("(1)入住    \n(2)预定    \n(3)房间信息编辑   \n(4)房间添加    \n(5)房间删除    \n(0)退出");
		printf("-----------------------------------------------------------------------------------------------------------------\n");
		printf("please chose:", &chose);
		switch (chose){
			case 0:

			case 1:
				printf("please input date of check in,like  20160420 \n >>");
				scanf("%d", &date_check_in);
				printf("please input date of check out,like 20160712 \n >>");
				scanf("%d", &date_check_out);
				//查询
				find_free_room(room_head, date_check_in, date_check_out, &bool_judge);//自动打印可用列表
				//用id预定
				printf("room id:");
				scanf("%d",&id);
				continue;
		   	case 2:
		   		printf("please input date of check in,like  20160420 \n >>");
				scanf("%d", &date_check_in);
				printf("please input date of check out,like 20160712 \n >>");
				scanf("%d", &date_check_out);
				find_free_room(room_head, date_check_in, date_check_out, &bool_judge);//自动打印可用列表
				printf("enter free room id:");
				scanf("%d", &id);
				hotel_reserve(user_head,id, date_check_in, date_check_out, &result);
				if (result == 1){
					printf("success!\n");
				}
				else{
					printf("sorry,fail,you can find technique help\n");
				}
				system("cls");
				continue;
			default:
				system("cls");
				printf("input err\n");
				continue;
		}
	}
	return 0;
}
