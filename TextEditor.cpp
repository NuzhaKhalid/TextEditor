#include <iostream>
#include <fstream>
#include "graphics.h"
using namespace std;

struct textNode {

	char ch;
	textNode* next, *prev;
};

void addText(textNode*& head, textNode*& tail, textNode*& cursor, char ch, int& size) {

	textNode* current = head;
	textNode* prev = nullptr;

	if (cursor == NULL && head == NULL && tail == NULL) {

		head = new textNode;        // head = tail = new node;
		head->ch = ch;
		head->next = NULL;
		head->prev = NULL;
		tail = cursor = head;
	}
	else if (cursor == NULL) {                //add at beginning
		head = new textNode;
		head->ch = ch;
		head->next = current;
		head->prev = NULL;
		cursor = head;
	}

	else {
		while (current != cursor) {
			prev = current;
			current = current->next;
		}
		textNode* newnode = new textNode;
		if (current == tail) {        //add at end
			current->next = newnode;
			newnode->ch = ch;
			tail = newnode;
			tail->next = NULL;
			tail->prev = current;
			cursor = tail;
		}
		else {                      // in between
			newnode->next = current->next;
			newnode->prev = current;
			current->next = newnode;
			newnode->ch = ch;
			cursor = newnode;
		}
	}
	size++;
}
void removeText(textNode*& head, textNode*& tail, textNode*& cursor, char ch, int& size) {

	if (!head)
		return;
	textNode* prev = NULL;
	textNode* current = head;
	textNode* nxt = current->next;

	if (cursor == head && cursor->prev == NULL) {                           // beginning

		if (current->next != NULL) {
			head = current->next;
			if (current)
				delete current;
			head->prev = NULL;
			cursor = head;
		}
		else {
			head = NULL;
			if (current)
				delete current;
			cursor = tail = head;
		}

	}
	else {
		while (cursor != current) {
			prev = current;
			current = current->next;
			nxt = current->next;
		}
		if (current == tail) {                            //end
			delete tail;
			tail = prev;
			tail->next = NULL;
			cursor = tail;
		}
		else {                                       // in between
			delete current;
			prev->next = nxt;
			nxt->prev = prev;
			cursor = prev;
		}
	}
	size--;
}
void print(textNode* head, textNode* cursor, int size) {

	setbkcolor(1);
	int i = 0;
	char text[2] = { '\0', '\0' };
	textNode* temp = head;
	int x, y;
	x = 11, y = 11;
	rectangle(8, 8, getwindowwidth() - 25, getwindowheight() - 50);
	textNode* temp2 = head;
	while (i < size && temp != NULL) {
		text[0] = temp->ch;
		if(y <= getwindowheight() - 60)
			outtextxy(x, y, text);
		if (y > getwindowheight() - 60)
			return;
		if ((x > getwindowwidth() - 41 || text[0] == '\n')) {
			y += textheight(text);
			x = 11;
		}
		else {
			x += textwidth(text);
		}
		i++;
		if (temp == cursor) {
			setcolor(12);
			outtextxy(x, y, "|");
			x += textwidth("|");
			setcolor(15);
		}
		temp = temp->next;
	}
}
void printotherwid(textNode* head, textNode* cursor, int size, int flag) {

	int i = 0;
	char text[2] = { '\0', '\0' };
	textNode* temp = head;
	int x, y;
	if (flag == 2) {
		outtext(" Enter the file name:  ");
	}
	else if (flag == 3) {
		outtext(" Enter the string to be found:  ");
	}
	else if (flag == 4) {
		outtext(" Enter the string to be replaced:  ");
	}
	x = 3, y = 16;
	while (i < size) {
		text[0] = temp->ch;
		outtextxy(x, y, text);
		if (x > getwindowwidth() - 33 || text[0] == '\n') {
			y += textheight(text);
			x = 3;
		}
		else {
			x += textwidth(text);
		}
		i++;
		if (temp == cursor) {
			setcolor(12);
			outtextxy(x, y, "|");
			setcolor(15);
		}
		temp = temp->next;
	}
}
void Findandreplace(textNode*& head, textNode*& tail, textNode*& cursor, char *find, char *replace, int& size) {

	int findsize = 0, repsize = 0;
	while (find[findsize]) {
		findsize++;
	}
	while (replace[repsize]) {
		repsize++;
	}
	int newsize = 0;
	textNode* temp = head;
	int i = 0, j = 0, l = 0, flag = 0;
	char a, b, c;
	int k = 0;
	while (i < size && temp != NULL) {
		flag = 0;
		a = temp->ch;
		if (a == find[0]) {
			textNode* temp2 = temp;
			b = temp2->ch;
			j = 0;
			while (b == find[j]) {
				j++;
				temp2 = temp2->next;
				if (temp2 != NULL) {
					b = temp2->ch;
				}
				else
					break;
			}
			k = 0;
			if (j >= findsize) {

				while (k <= findsize && temp != NULL) {
					cursor = temp;
					c = temp->ch;
					temp = temp->next;
					removeText(head, tail, cursor, c, size);
					k++;
				}
				l = 0;
				if (temp == head)
					cursor = head->prev;
				while (replace[l]) {
					addText(head, tail, cursor, replace[l], size);
					l++;
				}
				if (cursor != head) {
					addText(head, tail, cursor, 32, size);
					cursor = cursor->prev;
				}
			}
		}
		if (temp != NULL)
			temp = temp->next;
		else
			break;
		i++;
	}
}
void printhighlighted(textNode* head, textNode* cursor, textNode* head2, textNode* tail2) {

	int i = 0;
	char text[2] = { '\0', '\0' };
	textNode* temp = head;
	int x, y;
	x = 11, y = 11;
	rectangle(8, 8, getwindowwidth() - 25, getwindowheight() - 50);

	while (temp) {
		if (temp == head2->next) {
			setbkcolor(0);
			while (temp != NULL && temp != tail2->next) {
				text[0] = temp->ch;
				outtextxy(x, y, text);
				if (x > getwindowwidth() - 41 || text[0] == '\n') {
					y += textheight(text);
					x = 11;
				}
				else {
					x += textwidth(text);
				}
				i++;
				if (temp == cursor) {
					setcolor(12);
					outtextxy(x, y, "|");
					x += textwidth("|");
					setcolor(15);
				}
				temp = temp->next;
			}
		}
		else {
			setbkcolor(1);
			text[0] = temp->ch;
			outtextxy(x, y, text);
			if (x > getwindowwidth() - 41 || text[0] == '\n') {
				y += textheight(text);
				x = 11;
			}
			else {
				x += textwidth(text);
			}
			i++;
			if (temp == cursor) {
				setcolor(12);
				outtextxy(x, y, "|");
				x += textwidth("|");
				setcolor(15);
			}
			temp = temp->next;
		}
	}
	setbkcolor(1);
}

char* cut(textNode*& head, textNode*& tail, textNode*& head2, textNode*& tail2, textNode*& cursor, int& size) {


	int i = 0, j = 0;
	textNode* temp = head2->next;
	temp = head2->next;
	while (temp != tail2->next && temp != NULL) {
		temp = temp->next;
		i++;
		j++;
	}
	i = 0;
	char* ch = new char[j + 1];
	int a = 0;
	temp = head2->next;
	while (temp != tail2->next && temp != NULL) {
		ch[a] = temp->ch;
		temp = temp->next;
		i++;
		cout << a << endl;
		a++;
	}
	temp = head2->next;
	while (temp != tail2->next && temp != NULL) {
		temp = temp->next;
		if (temp && temp->prev)
			delete temp->prev;
	}
	if (temp)
		temp->prev = head2;
	head2->next = temp;

	cursor = head2;

	ch[j] = '\0';
	return ch;
}
char* copy(textNode*& head, textNode*& head2, textNode*& tail2, textNode*& cursor, int size) {

	int i = 0, j = 0;
	textNode* temp = head2->next;
	temp = head2->next;
	while (temp != tail2->next && temp != NULL) {
		temp = temp->next;
		i++;
		j++;
	}
	i = 0;
	char* ch = new char[j + 1];
	int a = 0;
	temp = head2->next;
	while (temp != tail2->next && temp != NULL) {
		ch[a] = temp->ch;
		temp = temp->next;
		i++;
		a++;
	}
	ch[j] = '\0';
	return ch;
}
void paste(textNode*& head, textNode*& tail, textNode*& cursor, char* ch, int& size)
{
	textNode* temp = cursor;
	int  i = 0;
	int num = strlen(ch);
	while (ch[i]) {
		temp = cursor;
		addText(head, tail, cursor, ch[i], size);
		i++;
	}
}

int main()
{
	int wid1, wid2;
	int width = 500;   
	int height = 400;
	wid1 = initwindow(width, height, "TextEditor");
	setcurrentwindow(wid1);
	textNode* text = NULL;                      // head
	textNode* tail = NULL;
	textNode* cursor = NULL;
	int size = 0;
	textNode* tail2 = NULL;
	textNode* head2 = NULL;
	int x = 11, y = 11;
	print(NULL, NULL, 0);

	char ch[2] = { '\0','\0' };
	rectangle(8, 8, getwindowwidth() - 25, getwindowheight() - 50);
	setbkcolor(1);
	setcolor(BLUE);
	setfillstyle(0, BLUE);
	floodfill(0, 0, WHITE);
	floodfill(width / 2, height / 2, WHITE);
	setcolor(WHITE);
	int count = 0;
	while (true)                      //keep displaying
	{
		ch[0] = getch();                        //read the key-press
		bool flag = 0;
		if (GetKeyState(VK_SHIFT) < 0)
			flag = 1;
		if (!flag) {
			count = 0;
			char* arr;
			if (ch[0] == 24) {              // cut  ctrl+X
				arr = cut(text, tail, head2, tail2, cursor, size);
				cleardevice();
				print(text, cursor, size);
			}
			else if (ch[0] == 22) {            //paste  ctrl+V
				paste(text, tail, cursor, arr, size);
				cleardevice();
				print(text, cursor, size);
			}
			else if (ch[0] == 3) {          // copy  ctrl+C 

				arr = copy(text, head2, tail2, cursor, size);
				setcolor(WHITE);
				setbkcolor(BLUE);

			}
			else if (ch[0] >= 32 && ch[0] <= 126) {
				addText(text, tail, cursor, ch[0], size);
				cleardevice();
				print(text, cursor, size);
			}
			else if (ch[0] == 8) {              // backspace
				removeText(text, tail, cursor, ch[0], size);
				cleardevice();
				print(text, cursor, size);
			}
			else if (ch[0] == 0) {
				ch[1] = getch();
				if (ch[1] == 75) {              // left key
					if (cursor->prev)
						cursor = cursor->prev;
					cleardevice();
					print(text, cursor, size);
				}
				else if (ch[1] == 77) {          //right key
					if (cursor->next)
						cursor = cursor->next;
					cleardevice();
					print(text, cursor, size);
				}
				else if (ch[1] == 72) {            // up arrow

					int i = 0, j = 0, k = 0, a = 0;
					while (cursor->ch != '\n' && cursor->prev!=NULL) {
						cursor = cursor->prev;
						i++;
					}
					if (cursor->prev == NULL && cursor!=NULL) {
						while (a < i) {
							cursor = cursor->next;
							a++;
						}
					}
					else {
						cursor = cursor->prev;
						while (cursor->ch != '\n' && cursor != text) {
							cursor = cursor->prev;
							j++;
						}
						while (k < i - 1) {
							cursor = cursor->next;
							k++;
						}
					}
					cleardevice();
					print(text, cursor, size);
				}
				else if (ch[1] == 80) {                   // down arrow

					int i = 1, j = 0;
					while (cursor->prev != NULL && cursor->ch != '\n') {

						cursor = cursor->prev;
						i++;
					}
					if(cursor->prev!=NULL)
						cursor = cursor->next;
					while (cursor->ch != '\n' && cursor->next != NULL) {
						cursor = cursor->next;
					}
					int k = 0;
					while (k < i && cursor->next != NULL) {
						cursor = cursor->next;
						k++;
					}
					cleardevice();
					print(text, cursor, size);
				}
			}
			else if (ch[0] == 13) {                //enter
				addText(text, tail, cursor, '\n', size);
				cleardevice();
				print(text, cursor, size);
			}
			else if (ch[0] == 15)                   // file load
			{
				wid2 = initwindow(400, 300, "FileDestination");
				setcurrentwindow(wid2);
				char file[100];
				file[0] = 0;
				outtext(" Enter the file name:  ");
				textNode* cursor2 = NULL;
				textNode* head2 = NULL;
				textNode* tail2 = NULL;
				int size2 = 0;
				int i;
				for (i = 0;; i++) {
					file[i] = getch();
					if (file[i] == 8) {
						removeText(head2, tail2, cursor2, file[i], size2);
						cleardevice();
						printotherwid(head2, cursor2, size2, 2);
					}
					else if (file[i] == 13) {
						break;
					}
					else {
						addText(head2, tail2, cursor2, file[i], size2);
						cleardevice();
						printotherwid(head2, cursor2, size2, 2);
					}
				}
				file[i] = 0;
				closegraph(wid2);
				setcurrentwindow(wid1);
				//cout << file << endl;
				char temp;
				ifstream load;
				load.open(file);
				char p = load.peek();
				if (load) {
					while (text)
						removeText(text, tail, text, 0, size);
					while (!load.eof()) {
						load.get(temp);
						addText(text, tail, cursor, temp, size);
						p = load.peek();
						cleardevice();
						print(text, cursor, size);
					}
				}
				else
					outtextxy(10, 15, " Error in opening file. ");
			}
			else if (ch[0] == 19) {                   // save in file
				ofstream savefile;
				savefile.open("output");
				int i = 0;
				textNode* temp = text;
				char c;
				while (i < size && temp != NULL) {
					c = temp->ch;
					savefile << c;
					temp = temp->next;
				}
				savefile.close();
			}
			else if (ch[0] == 6) {                  //replace ctrl+F
				int wid3, wid4;
				wid3 = initwindow(400, 300, "Find");
				setcurrentwindow(wid3);
				char find[100];
				outtext(" Enter the string to be found:  ");
				textNode* cursor2 = NULL;
				textNode* head2 = NULL;
				textNode* tail2 = NULL;
				int size2 = 0;
				int i;
				for (i = 0;; i++) {
					find[i] = getch();
					if (find[i] == 8) {
						removeText(head2, tail2, cursor2, find[i], size2);
						cleardevice();
						printotherwid(head2, cursor2, size2, 3);
					}
					else if (find[i] == 13) {
						break;
					}
					else {
						addText(head2, tail2, cursor2, find[i], size2);
						cleardevice();
						printotherwid(head2, cursor2, size2, 3);
					}
				}
				find[i] = 0;
				closegraph(wid3);
				wid4 = initwindow(400, 300, "Replace");
				setcurrentwindow(wid4);
				char replace[100];
				outtext(" Enter the string to be replaced:  ");
				textNode* cursor3 = NULL;
				textNode* head3 = NULL;
				textNode* tail3 = NULL;
				int size3 = 0;
				for (i = 0;; i++) {
					replace[i] = getch();
					if (replace[i] == 8) {
						removeText(head3, tail3, cursor3, replace[i], size3);
						cleardevice();
						printotherwid(head3, cursor3, size3, 4);
					}
					else if (replace[i] == 13) {
						break;
					}
					else {
						addText(head3, tail3, cursor3, replace[i], size3);
						cleardevice();
						printotherwid(head3, cursor3, size3, 4);
					}
				}
				replace[i] = 0;
				closegraph(wid4);
				setcurrentwindow(wid1);
				Findandreplace(text, tail, cursor, find, replace, size);
				cleardevice();
				print(text, cursor, size);
			}
		}
		else {                                 // pressed with shift key
			if (ch[0] == 0) {
				ch[0] = getch();
				if (ch[0] == 75) {               //left key
					if (count == 0) {
						tail2 = cursor;
						head2 = cursor->prev;
						count = 1;
						cursor = cursor->prev;
					}
					else {
						if (cursor->prev)
							cursor = cursor->prev;
						head2 = cursor;
					}
					cleardevice();
					printhighlighted(text, cursor, head2, tail2);
				}
				else if (ch[0] == 77) {        //right key

					if (count == 0) {
						head2 = cursor;
						tail2 = cursor->next;
						count = 1;
						cursor = cursor->next;
					}
					else {
						if (cursor->next)
							cursor = cursor->next;
						tail2 = cursor;
					}

					cleardevice();
					printhighlighted(text, cursor, head2, tail2);
				}
			}
			else if (ch[0] >= 32 && ch[0] <= 126) {
				count = 0;
				addText(text, tail, cursor, ch[0], size);
				cleardevice();
				print(text, cursor, size);
			}
		}
	}
	return 0;
}