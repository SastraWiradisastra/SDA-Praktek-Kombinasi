#include "structure.h"

elmtAddress allocate(string title, Length len, string album, string artist)
{
	elmtAddress newNode;
        
        newNode = (elmtAddress)malloc(sizeof(Elmt));
        if(newNode != NULL)
        {
                newNode->title = strdup(title);
		newNode->len = len;
		newNode->album = strdup(album);
		newNode->artist = strdup(artist);
                newNode->next = NULL;
        }
    
        return (newNode);

}

void createList(List* playlist)
{
	(*playlist).front = NULL;
	(*playlist).rear = NULL;
}

void deallocate(elmtAddress node)
{
	if(node != NULL)
	{
		free((string)node->title);
		free((string)node->album);
		free((string)node->artist);
		free(node);
	}
}

void deleteList(List* playlist)
{
	elmtAddress nodeToDel;

	nodeToDel = (*playlist).front;
	while (nodeToDel != NULL)
	{
		(*playlist).front = nodeToDel->next;
		deallocate(nodeToDel);
		nodeToDel = (*playlist).front;
	}
}

bool listEmpty(List playlist)
{
	return(playlist.front == NULL);
}

bool sameElmt(Elmt node, Elmt nodeToComp)
{
	return
	(
		strcasecmp(node.title, nodeToComp.title) == 0 &&
		strcasecmp(node.album, nodeToComp.album) == 0 &&
		strcasecmp(node.artist, nodeToComp.artist) == 0
	);
}

int compareTitle(elmtAddress a, elmtAddress b) 
{
    	return strcasecmp(a->title, b->title);
}

int compareLength(elmtAddress a, elmtAddress b) 
{
	unsigned long totalA = a->len.hours * 3600 + a->len.minutes * 60 + a->len.seconds;
	unsigned long totalB = b->len.hours * 3600 + b->len.minutes * 60 + b->len.seconds;
	
	return totalA - totalB;
}

int compareAlbum(elmtAddress a, elmtAddress b) 
{
    	return strcasecmp(a->album, b->album);
}

int compareArtist(elmtAddress a, elmtAddress b) 
{
    	return strcasecmp(a->artist, b->artist);
}

int getTotalElmt(List playlist)
{
	int count = 0;
	elmtAddress node;

	if (playlist.front != NULL)
	{
		node = playlist.front;

		for (;;)
		{
			if (node == NULL)
				break;
			else 
			{
				count++;
				node = node->next;
			}
		} 
	}
	
	return(count);
}

void copyList(List playlist, List* playlistCopy)
{
	createList(playlistCopy);
	elmtAddress curr = playlist.front;

	while(curr != NULL)
	{
		elmtAddress newNode = allocate(curr->title, curr->len, curr->album, curr->artist);
		insRear(playlistCopy, newNode);
		curr = curr->next;
	}
}

void printElmt(elmtAddress node)
{
	printf("Title\t: %s\n", node->title);
	printf("Length\t: %u:%u:%u\n", 
		node->len.hours,
		node->len.minutes,
		node->len.seconds);
	printf("Album\t: %s\n", node->album);
	printf("Artist\t: %s\n", node->artist);
}

void printList(List playlist)
{
	elmtAddress node;

	if(playlist.front == NULL)
	{
		perror("Playlist kosong!\n");
	}

	node = playlist.front;
	for(;;)
	{
		if(node == NULL)
		{
			printf("\n");
			break;
		}
		else
		{
			printElmt(node);
			node = node->next;
		}
	}
}

void splitList(elmtAddress source, elmtAddress* front, elmtAddress* back) 
{
    elmtAddress fast = source->next;
    elmtAddress slow = source;
    
    while (fast != NULL) 
    {
        fast = fast->next;
        if (fast != NULL) 
	{
            slow = slow->next;
            fast = fast->next;
        }
    }
    
    *front = source;
    *back = slow->next;
    slow->next = NULL;
}

elmtAddress merge(elmtAddress a, elmtAddress b, int (*compare)(elmtAddress, elmtAddress))
{
	if (a == NULL) 
		return b;
    	
	if (b == NULL) 
		return a;

    	if (compare(a, b) <= 0) 
	{
        	a->next = merge(a->next, b, compare);
        	return a;
    	} 
	else 
	{
        	b->next = merge(a, b->next, compare);
        	return b;
    	}
}

void mergeSort(elmtAddress* headRef, int (*compare)(elmtAddress, elmtAddress)) 
{
    	elmtAddress head = *headRef;
    	if(head == NULL || head->next == NULL) 
		return;

    	elmtAddress a, b;
    	splitList(head, &a, &b);
    	mergeSort(&a, compare);
    	mergeSort(&b, compare);
    	*headRef = merge(a, b, compare); 
}

void sortList(List* playlist, toSort sort)
{
	int (*comparator)(elmtAddress, elmtAddress) = NULL;
	
	switch(sort)
	{
		case SORT_TITLE:
			comparator = compareTitle;
			break;
		case SORT_LENGTH:
			comparator = compareLength;
			break;
		case SORT_ALBUM:
			comparator = compareAlbum;
			break;
		case SORT_ARTIST:
			comparator = compareArtist;
			break;
	}
	
	mergeSort(&playlist->front, comparator);
}
	
void inverseList(List* playlistCopy)
{
	elmtAddress node, newNode;
	List temp;

	createList(&temp);
	node = (*playlistCopy).front;
	while (node != NULL)
	{
		newNode = node;
		node = node->next;
		(*playlistCopy).front = node;
		newNode->next = NULL;
		insFront(&temp, newNode);
	} 
	(*playlistCopy).front = temp.front;
}

elmtAddress searchList(List playlist, string query)
{	
	elmtAddress node;
	bool found = false;

	node = playlist.front;
	while((node != NULL) && (!found))
	{
		if(strcasecmp(query, node->title) == 0
			|| strcasecmp(query, node->album) == 0
			|| strcasecmp(query, node->artist) == 0)
			found = true;
		else
			node = node->next;
	} 
	
	return(node);	
}

void insFront(List* playlist, elmtAddress node)
{
	node->next = (*playlist).front;
	(*playlist).front = node;
}

void insRear(List* playlist, elmtAddress node)
{
	if ((*playlist).front == NULL) 
	{
        	(*playlist).front = node;
        	(*playlist).rear = node;
    	} 
	else 
	{
        	(*playlist).rear->next = node;
        	(*playlist).rear = node;
    	}
}

void insManual(List* playlist, elmtAddress node, unsigned int pos)
{
	if(pos == 1)
	{
		insFront(playlist, node);
		return;
	}
	
	if(pos == (getTotalElmt(*playlist) + 1))
	{
		insRear(playlist, node);
		return;
	}

	elmtAddress curr = (*playlist).front;
	for(int i = 1; i < (pos - 1) && curr != NULL; i++)
		curr = curr->next;

	node->next = curr->next;
	curr->next = node;
}

void delFront(List* playlist)
{
	elmtAddress nodeToDel;

	nodeToDel = (*playlist).front;
	(*playlist).front = (*playlist).front->next;
	deallocate(nodeToDel);
}

void delRear(List* playlist)
{
	elmtAddress nodeToDel, prev;

	nodeToDel = (*playlist).front;
	prev = NULL;
	
	while (nodeToDel->next != NULL)
	{
		prev = nodeToDel;
		nodeToDel = nodeToDel->next;
	}
    	
	if(prev) 
		prev->next = NULL;
    	else 
		playlist->front = NULL;
    
    	playlist->rear = prev;
    	deallocate(nodeToDel);
}

void delManual(List* playlist, unsigned int pos)
{
	if (pos == 1) 
	{
        	delFront(playlist);
        	return;
    	}

	if(pos == (getTotalElmt(*playlist) + 1))
	{
		delRear(playlist);
		return;
	}

    	elmtAddress prev = playlist->front;
    	for (int i = 1; prev != NULL && i < pos - 1; i++) 
	{
        	prev = prev->next;
    	}

	elmtAddress nodeToDel = prev->next;
    	prev->next = nodeToDel->next;
    
    	if (nodeToDel == playlist->rear) 
	{
        	playlist->rear = prev;
    	}
    
    	deallocate(nodeToDel);
}
