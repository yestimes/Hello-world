//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myfile.h"

int main(void) 
{
	//�������ñ���
	int bool_judge = 0;
	int ret = 0;
	int result = 0;
	//����ͷ�ʹ�ñ���
	int date_check_in = 0;
	int date_check_out = 0;
	//main����ʹ�ñ���
	char user_name[16];
	char user_passwd[16];
	room *room_head = NULL;
	user *user_head = NULL;
	//��ʼ����
	int m = 1; 
	int n = 1;
	int chose = 1;
	int i = 0;
	user *user_id = NULL;
	int id = 0;
	//������������
	load_userdata(&user_head);
	ret = 0;
	load_roomdata(&room_head, &ret);
	printf("--------welcome to the hotel management system--------\n");
	while (m){
	printf("1.register \n2.login \nother.exit \nenter :");
	scanf("%d",&chose);
	printf("\n");
	//�ظ�У���û���Ϣ
		switch(chose) {
			case 1:
				//�û�ע�� 
				while(n){
					printf("enter a new user name:");
					gets(user_name);
					printf("enter passwd:");
					gets(user_passwd);
					ret = user_register(user_head, user_name, user_passwd, &bool_judge);
					if (ret != 0){
						printf("�Ƿ�������\n");
						return -1;
					}
					if (bool_judge == 1){
					 	printf("err:registered fail,user-name has registered\n");
					 	printf("continue register, please input 1,other input will exit\n");
					 	scanf("%d",&i);
						//�˳���ѭ�� 
					 	if(i != 1){
					 		n = 0;
						 }
						continue;
					 }
				}
				break;
			case 2:
				//�û���¼ 
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
						 	//�˳���ѭ�� 
							break;
			    		 }
						continue;
					}
					else if (bool_judge == -2){
						printf("err:user password incorrect\n");
					}else{
						m = 0;
						break;
						//�˳���ѭ�� 
					}
				} 
				break;
			default:
				//�˳� 
				break;
				return 0;
		}
    }
	//��ʼ����������
	i = 0; chose = 0;
	m = 0; n = 0;
	//�������
	if (user_id == NULL){
		printf("user do not login success\n");
		return -1;
	}
	system("cls");
	printf("---%s-----welcome to the hotel management system--------\n",user_id->name);
	m = 1;
	while (m){
		printf("----------------------please input sums to chose\n----------------\n");
		printf("(1)��ס    \n(2)Ԥ��    \n(3)������Ϣ�༭   \n(4)�������    \n(5)����ɾ��    \n(0)�˳�");
		printf("-----------------------------------------------------------------------------------------------------------------\n");
		printf("please chose:", &chose);
		switch (chose){
			case 0:

			case 1:
				printf("please input date of check in,like  20160420 \n >>");
				scanf("%d", &date_check_in);
				printf("please input date of check out,like 20160712 \n >>");
				scanf("%d", &date_check_out);
				//��ѯ
				find_free_room(room_head, date_check_in, date_check_out, &bool_judge);//�Զ���ӡ�����б�
				//��idԤ��
				printf("room id:");
				scanf("%d",&id);
				continue;
		   	case 2:
		   		printf("please input date of check in,like  20160420 \n >>");
				scanf("%d", &date_check_in);
				printf("please input date of check out,like 20160712 \n >>");
				scanf("%d", &date_check_out);
				find_free_room(room_head, date_check_in, date_check_out, &bool_judge);//�Զ���ӡ�����б�
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
