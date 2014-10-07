#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <stdint.h>

#include "terminal/getch.h"
#include "terminal/tool_interact.h"

namespace cupid
{
static const int MAX_CMD_LEN = 4096;

struct history_cmd_node_t
{
	std::string cmd;
	history_cmd_node_t* pre;
	history_cmd_node_t* next;

	history_cmd_node_t()
	{
		pre = NULL;
		next = NULL;
	}

	history_cmd_node_t(std::string _cmd, 
							history_cmd_node_t* _pre,
							history_cmd_node_t* _next)
	{
		cmd = _cmd;
		pre = _pre;
		next = _next;
	}
};

static history_cmd_node_t* g_history_cmd_head = new history_cmd_node_t();

enum control_key_t
{
	UP_ARROW=-128, 
	DOWN_ARROW, 
	RIGHT_ARROW, 
	LEFT_ARROW, 
	DELETE, 
	PAGE_UP, 
	PAGE_DOWN,
	BACKSPACE, 
	ESC, 
	ENTER,
};

int keycode(int c)
{
	if (27 == c)
	{
		c = cupid::cupid_getch();
		if (91 == c)
		{
			c = cupid::cupid_getch();
			if (65 == c)
			{
				c = UP_ARROW;
			}
			else if (66 == c)
			{
				c = DOWN_ARROW;
			}
			else if (67 == c)
			{
				c = RIGHT_ARROW;
			}
			else if (68 == c)
			{
				c = LEFT_ARROW;
			}
			else if (51 == c)
			{
				c = cupid::cupid_getch();
				if (126 == c)
				{
					c = DELETE;
				}
			}
			else if (53 == c)
			{
				c = cupid::cupid_getch();
				if (126 == c)
				{
					c = PAGE_UP;
				}
			}
			else if (54 == c)
			{
				c = cupid::cupid_getch();
				if (126 == c)
				{
					c = PAGE_DOWN;
				}
			}
		}
		else if (27 == c)
		{
			c = ESC;
		}
	}
	else if (8 == c)
	{
		c = BACKSPACE;
	}
	else if (10 == c)
	{
		c = ENTER;
	}

	return c;
}

void init_history_cmd_double_link()
{
	g_history_cmd_head->next = g_history_cmd_head;
	g_history_cmd_head->pre = g_history_cmd_head;
}


std::string get_line()
{
	std::string cmd;
	bool run_loop = true;
	history_cmd_node_t* history_cmd_pos = g_history_cmd_head;
	int curse_pos = 0;
	
	while (run_loop)
	{
		char c = cupid::cupid_getch();
		c = keycode(c);
		history_cmd_node_t* node = NULL;

		uint32_t tmp_int = 0;
		char tmp_char = '\0';

		switch(c)
		{
		case BACKSPACE:
		case DELETE:
			if (curse_pos > 0)
			{
				printf("\b");
				for(uint32_t i=curse_pos; i<cmd.size(); ++i)
				{
					printf("%c", cmd[i]);
				}
				printf(" ");
				tmp_int = cmd.size()+1-curse_pos;
				for(uint32_t i=0; i<tmp_int; ++i)
				{
					printf("\b");
				}
				cmd.erase(curse_pos - 1, 1);
				--curse_pos;
			}
			break;
		case ENTER:
			run_loop = false;
			printf("\n");
			node = new history_cmd_node_t();
			node->cmd = cmd;
			node->next = g_history_cmd_head->next;
			node->pre = g_history_cmd_head;
			g_history_cmd_head->next->pre = node;
			g_history_cmd_head->next = node;

			curse_pos = 0;
			break;
		case UP_ARROW:
			if (history_cmd_pos->next != g_history_cmd_head)
			{
				history_cmd_pos = history_cmd_pos->next;

				if (curse_pos > 0)
				{
					for (int i=0; i<curse_pos; ++i)
					{
						printf("\b \b");
					}
				}
				cmd = history_cmd_pos->cmd;
				printf("%s", cmd.c_str());

				curse_pos = cmd.size();
			}
			break;
		case DOWN_ARROW:
			if (history_cmd_pos != g_history_cmd_head)
			{
				history_cmd_pos = history_cmd_pos->pre;

				if (curse_pos > 0)
				{
					for (int i=0; i<curse_pos; ++i)
					{
						printf("\b \b");
					}
				}
				
				cmd = history_cmd_pos->cmd;
				printf("%s", cmd.c_str());

				curse_pos = cmd.size();
			}
			break;
		case RIGHT_ARROW:
			if (curse_pos < (int)cmd.size())
			{
				tmp_char = cmd[curse_pos];
				printf("%c", tmp_char);
				++curse_pos;
			}
			break;
		case LEFT_ARROW:
			if (curse_pos > 0)
			{
				printf("\b");
				--curse_pos;
			}
			break;
		case PAGE_UP:
		case PAGE_DOWN:
			// ignore
			break;
		case ESC:
			printf("\n");
			exit(0);
		default:
			printf("%c", c);
			cmd.insert(curse_pos, 1, c);
			++curse_pos;
			for (tmp_int=curse_pos; tmp_int<cmd.size(); ++tmp_int)
			{
				printf("%c", cmd[tmp_int]);
			}
			for (tmp_int = cmd.size(); (int)tmp_int > curse_pos; --tmp_int)
			{
				printf("\b");
			}
			break;
		}

	}

	cmd.append(1, '\0');
	
	return cmd;
}

} // end of namespace cupid
