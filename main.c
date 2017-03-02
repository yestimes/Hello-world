#define _CRT_SECURE_NO_WARNINGS
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
	//�û�����
	int m = 1; 
	int n = 1;
	int chose = 1;
	int i = 0;
	int temp_use_edit = 1;
	user *user_id = NULL;
	room *room_edit = NULL;
	int id = 0;
	char guest_name[16];
	int temp_sum = 0;
	char *state_to_string[3] = { "free", "using", "wait" };
	int first_time = 0;
	int second_time = 0;
	//������������
	load_userdata(&user_head);
	ret = 0;
	load_roomdata(&room_head, &ret);
	printf("--------welcome to the hotel management system--------\n");
	while (m){
	printf("1.register \n2.login \nother.exit \nenter :");
	scanf("%d", &chose); 
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
					getchar();
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
		printf("press any key to continue\n");
		getchar();
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
		case 0://�˳�����
			//�����û�
			//����ԤԼ
			//���淿��
			//�ͷſռ�
			free_user(user_head, &result);
			if (result != 1){
				printf("free user err ��رպ�����������������ڴ�й©\n");
				printf("press any key to continue\n");
				getchar();
				return -1;
				break;
			}
			free_all_room(room_head, &result);
			if (result != 1){
				printf("free room err ��رպ�����������������ڴ�й©\n");
				printf("press any key to continue\n");
				getchar();
				return -1;
				break;
			}
			break;

		case 1://(1)��ס 
			printf("please input date of check in,like  20160420 \n >>");
			scanf("%d", &date_check_in);
			printf("please input date of check out,like 20160712 \n >>");
			scanf("%d", &date_check_out);
			//��ѯ
			find_free_room(room_head, date_check_in, date_check_out, &bool_judge);//�Զ���ӡ�����б�
			//��idԤ��
			printf("room id:");
			scanf("%d", &id);
			continue;
		case 2://Ԥ��
			printf("please input date of check in,like  20160420 \n >>");
			scanf("%d", &date_check_in);
			printf("please input date of check out,like 20160712 \n >>");
			scanf("%d", &date_check_out);
			find_free_room(room_head, date_check_in, date_check_out, &bool_judge);//�Զ���ӡ�����б�
			printf("enter free room id:");
			scanf("%d", &id);
			printf("please input Mr guest 's name:");
			gets(guest_name);
			hotel_reserve(room_head, guest_name, id, date_check_in, date_check_out, &result);

			if (result == 1){
				printf("success!\n");
			}
			else{
				printf("sorry,fail,you can find technique help\n");
				printf("press any key to continue\n");
				getchar();
			}
			system("cls");
			i = 1;
			continue;
		case 3://������Ϣ�༭
			while (i){
				system("cls");
				printf("edit (0)name_guest (1)state (2)price (3)time of start or time of end (other) exit\n");
				printf("chose :");
				result = 0;
				scanf("%d", &n);
				switch (n){
				case 0:
					printf("please input room id:");
					scanf("%d", &id);
					printf("enter new guest name:");
					gets(guest_name);
					edit_room(room_head, n, id, guest_name, 0, 0, 0, 0, &result);
					if (result == 1){
						printf("success , new name is %s \n", guest_name);
						printf("you may need (0)exit edit menu (1) continue edit chose:");
						scanf("%d", &chose);
						if (chose == 1){
							break;
						}
						else{
							i = 0;
							break;
						}
					}
					else{
						printf("err edit fail\n");
						printf("press any key to continue\n");
						getchar();
						break;
					}
				case 1:
					printf("please input room id:");
					scanf("%d", &id);
					find_room_by_id(id, room_head, &room_edit, &result);
					if (result != 1){
						printf("room of this id do not find\n");
						printf("press any key to continue\n");
						break;
					}
					printf("guest is %s ,enter new name:", room_edit->name_guest);
					scanf("%d", &temp_use_edit);
					edit_room(room_head, n, id,"null", 0, temp_use_edit, 0, 0, &result);
					if (result == 1){
						printf("success , new price is %d \n", temp_use_edit);
						printf("you may need (0)exit edit menu (1) continue edit chose:");
						scanf("%d", &chose);
						if (chose == 1){
							break;
						}
						else{
							i = 0;
							break;
						}
					}
					else{
						printf("err edit fail\n");
						printf("press any key to continue\n");
						getchar();
						break;
					}
				case 2:
					printf("please input room id:");
					scanf("%d", &id);
					find_room_by_id(id, room_head, &room_edit, &result);
					if (result != 1){
						printf("room of this id do not find\n");
						printf("press any key to continue\n");
						getchar();
						break;
					}
					printf("now price is %d, enter new price:", room_edit->price);
					scanf("%d", &temp_use_edit);
					edit_room(room_head, n, id, "null", 0, temp_use_edit, 0, 0, &result);
					if (result == 1){
						printf("success , new price is %d \n", temp_use_edit);
						printf("you may need (0)exit edit menu (1) continue edit chose:");
						scanf("%d", &chose);
						if (chose == 1){
							break;
						}
						else{
							i = 0;
							break;
						}
					}
					else{
						printf("err edit fail\n");
						printf("press any key to continue\n");
						getchar();
						break;
					}
				case 3:
					printf("please input room id:");
					scanf("%d", &id);
					find_room_by_id(id, room_head, &room_edit, &result);
					if (result != 1){
						printf("room of this id do not find\n");
						printf("press any key to continue\n");
						getchar();
						break;
					}
					printf("Mr guest start at %d, end at %d ,enter two time update it:first >>", room_edit->t_start, room_edit->t_end);
					scanf("%d", &first_time);
					printf("second>>");
					scanf("%d", &second_time);
					if (second_time < first_time){
						printf("err :first time < second time\n");
						printf("press any key to continue\n");
						getchar();
						break;
					}
					edit_room(room_head, n, id, "null", 0, temp_use_edit, 0, 0, &result);
					if (result == 1){
						printf("success , new price is %d \n", temp_use_edit);
						printf("you may need (0)exit edit menu (1) continue edit chose:");
						scanf("%d", &chose);
						if (chose == 1){
							break;
						}
						else{
							i = 0;
							break;
						}
					}
					else{
						printf("err edit fail\n");
						printf("press any key to continue\n");
						getchar();
						break;
					}
				case 4://add room
					i = 1;
					while (i){
						room_edit = room_head;
						printf("-------id------state------");
						while (room_edit != NULL){
							printf("--------%d---------%s-----\n", room_edit->id, state_to_string[room_edit->state]);
						}
						printf("please set a id , do not same as one:");
						scanf("%d", &id);
						printf("how many much a night?");
						scanf("%d", &temp_sum);
						if (temp_sum <= 0){
							printf("price incorrect \n");
							printf("press any key to continue\n");
							getchar();
							continue;
						}
						//idУ��
						find_room_by_id(id, room_head, &room_edit, &result);
						if (result == 1){
							printf("id as the same \n");
							printf("press any key to continue\n");
							getchar();
							continue;
						}
						room_add(room_head, id, temp_sum, &result);
						i = 0;
						break;
					}
				case 5:
					printf("please set a id , do not same as one:");
					scanf("%d", &id);
					find_room_by_id(id, room_head, &room_edit, &result);
					if (result != 1){
						printf("find room fail\n");
						printf("press any key to continue\n");
						getchar();
						break;
					}
					free_reserve(room_edit, &result);
					if (result != 1){
						printf("del room reserve  fail\n");
						printf("press any key to continue\n");
						getchar();
						break;
					}
					if (room_edit != NULL){
						free(room_edit);
						room_edit = NULL;
					}
					break;
				}
		default:
			system("cls");
			printf("input err\n");
			printf("press any key to continue\n");
			getchar();
			continue;
			}
		}
		return 0;
	}
}
