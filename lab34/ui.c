#include "ui.h"



int addSubstance_ui(DynamicArray* substRepo, char *command)
{

	char catalogingNumber[21];
	char state[45];
	char intendedUse[45];
	char potency[21];

	command = strtok(NULL, " ,");
	if (command == NULL)
	{
		return -1;
	}
	strcpy(catalogingNumber, command);

	command = strtok(NULL, " ,");
	if (command==NULL)
	{
		return -1;
	}
	strcpy(state, command);

	command = strtok(NULL, " ,");
	if (command==NULL)
	{
		return -1;
	}
	strcpy(intendedUse, command);

	command = strtok(NULL, " ,");
	if (command==NULL)
	{
		return -1;
	}
	strcpy(potency, command);

	command = strtok(NULL, " ,");
	if (command!=NULL)
	{
		return -1;
	}

	return addSubstance_service(substRepo, catalogingNumber, state, intendedUse, atoi(potency));

}

int updateSubstance_ui(DynamicArray* substRepo, char *command)
{
	char catalogingNumber[21];
	char state[45];
	char intendedUse[45];
	char potency[21];
	command = strtok(NULL, " ,");
	if (command == NULL)
	{
		return -1;
	}
	strcpy(catalogingNumber, command);

	command = strtok(NULL, " ,");
	if (command == NULL)
	{
		return -1;
	}
	strcpy(state, command);

	command = strtok(NULL, " ,");
	if (command == NULL)
	{
		return -1;
	}
	strcpy(intendedUse, command);

	command = strtok(NULL, " ,");
	if (command == NULL)
	{
		return -1;
	}
	strcpy(potency, command);

	command = strtok(NULL, " ,");
	if (command != NULL)
	{
		return -1;
	}

	return updateSubstance_service(substRepo, catalogingNumber, state, intendedUse, atoi(potency));

}

int deleteSubstance_ui(DynamicArray* substRepo, char *command)
{
	char catalogingNumber[21];
	command = strtok(NULL, " ,");
	if (command==NULL)
	{
		return -1;
	}
	strcpy(catalogingNumber, command);
	command = strtok(NULL, " ,");
	if (command != NULL)
	{
		return -1;
	}
	return deleteSubstance_service(substRepo, catalogingNumber);
	
}

int list_ui(DynamicArray *substRepo, char *command)
{
	char listOfSubstances[200];
	listOfSubstances[0] = 0;
	command = strtok(NULL, " ");
	if (command == NULL)
	{
		listSubstances(substRepo, listOfSubstances);
	}
	else
	{
		char intendedUse[21];
		strcpy(intendedUse, command);
		command = strtok(NULL, " ");
		if (command!=NULL)
		{
			return -1;
		}
		int potencyLess = atoi(intendedUse);
		if (potencyLess == 0) {
			listSubstancesByIntendedUse(substRepo, intendedUse, listOfSubstances);
		}
		else
		{
			listPotencyLessThan(substRepo, potencyLess, listOfSubstances);
		}
	}

	printf("%s", listOfSubstances);
	return 1;
}

int listByPotency_ui(DynamicArray* substRepo, char* command)
{
	char listOfSubstances[42];
	listOfSubstances[0] = 0;
	command = strtok(NULL, " ");
	if (command != NULL) { return -1; }
	listDecreasingPotency(substRepo, listOfSubstances);
	printf("%s", listOfSubstances);
	return 1;
}

int listMaximumPotency_ui(DynamicArray* substRepo, char* command)
{
	char listOfSubstances[42];
	listOfSubstances[0] = 0;
	command = strtok(NULL, " ");
	if (command != NULL) { return -1; }
	listMaximumPotency(substRepo, listOfSubstances);
	printf("%s", listOfSubstances);
	return 1;
}

void help_menu()
{
	printf("To add a new substance the command is: add 'x,y,z,t'\n");
	printf("To update a substance, the command is: update 'x,t,z,y'. x must exist\n");
	printf("To delete a substance, the command is: delete 'x'. x must exist\n");
	printf("To list the substances, the command is: list\n");
	printf("To list the substances with a specific intended use, the command is: list 'abc'\n");
	printf("To list the substances with a potency less than a given value, the command is: list 'dec'\n");
	printf("To list the maximum potency, the command is: 'listMaximumPotency'\n");
	printf("To list the substances by potency decreasing, the command is:'listPotency'\n");
	printf("To undo, the command is: 'undo'\n");
	printf("To redo, the command is: 'redo'\n");
	printf("To exit, the command is:'exit'\n");
}


void start(DynamicArray* substRepo, DynamicArray* repoStack)
{
	addArray(repoStack, substRepo);
	int indexForUndoRedo = 0;
	
	
	
	help_menu();
	while (1)
	{
		
		char inputString[100];
		char* partialCommand;
		char command[11];


		scanf("%[^\n]%*c", inputString);

		partialCommand = strtok(inputString, " ");

		strcpy(command, partialCommand);

		DynamicArray* aux = repoStack->copy(repoStack->elems[indexForUndoRedo]);
		
		int validator = -1;


		if (strcmp(command, "add") == 0)
		{
			validator = addSubstance_ui(aux, partialCommand);

			if (validator == 1)
				addArray(repoStack, aux);
			indexForUndoRedo = repoStack->size - 1;
			
		}

		else if (strcmp(command, "update") == 0)
		{
			validator = updateSubstance_ui(aux, partialCommand);

			if (validator == 1)
				addArray(repoStack, aux);
			indexForUndoRedo = repoStack->size - 1;
			
		}

		else if (strcmp(command, "delete") == 0)
		{
			validator = deleteSubstance_ui(aux, partialCommand);
			if (validator == 1)
				addArray(repoStack, aux);
			indexForUndoRedo = repoStack->size - 1;
		}

		else if (strcmp(command, "listPotency") == 0)
		{
			validator = listByPotency_ui(aux, partialCommand);
		}

		else if (strcmp(command, "list") == 0)
		{
			validator = list_ui(aux, partialCommand);
		}
		else if (strcmp(command, "listMaximumPotency") == 0)
		{
			validator = listMaximumPotency_ui(aux, partialCommand);
		}

		else if (strcmp(command, "undo") == 0)
		{
			if (indexForUndoRedo > 0)
			{
				
				indexForUndoRedo--;
				validator = 1;
			
			}
			else
				validator = -1;
		}
		else if (strcmp(command, "redo") == 0)
		{
			if (indexForUndoRedo < aux->size + 1 ) 
			{

				indexForUndoRedo++;
				validator = 1;
			
			}
			else
				validator = -1;
		}

		else if (strcmp(command, "exit") == 0)
		{
			//destroySubstance(aux->elems);
			destroyArray(aux);
			return;
		}

		if (validator < 0)
		{
			printf("No!\n");
			destroyArray(aux);
			continue;
		}
		
		destroyArray(aux);
		
	}
}