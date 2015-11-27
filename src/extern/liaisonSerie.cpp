#include  "..\..\include\extern\liaisonSerie.h"

Serial::Serial(char *portName)
{
    //We're not yet connected
    this->connected = false;

    //On crée notre objet Handle
    this->hSerial = CreateFile(portName,
            GENERIC_READ | GENERIC_WRITE,
            0,
            NULL,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            NULL);

    //On vérifie si la connexuion est bien effectuée et si non...
    if(this->hSerial==INVALID_HANDLE_VALUE)
    {
        //On recherche la dernière erreur et on l'affiche
        if(GetLastError()==ERROR_FILE_NOT_FOUND){

            //Print Error if neccessary
            printf("ERROR: Handle was not attached. Reason: %s not available.\n", portName);

        }
        else
        {
            printf("ERROR!!!");
        }
    }
    else
    {
        // ON initialise les paramètres de connection
        DCB parametredcb = {0};

        //On recherche les paramètres actuels de connection

        if (!GetCommState(this->hSerial, &parametredcb))
        {
            //Si impossible, envoyer erreur
            printf("failed to get current serial parameters!");
        }
        else
        {
            //On modifie les paramètres.
            parametredcb.BaudRate=CBR_9600;
            parametredcb.ByteSize=8;
            parametredcb.StopBits=ONESTOPBIT;
            parametredcb.Parity=NOPARITY;

             //On envoie les paramètres à la liaison série et on vérifie leur bonne utilisation.
             if(!SetCommState(hSerial, &parametredcb))
             {// Si il y'a une erreur
                printf("ALERT: Could not set Serial Port parameters");
             }
             else
             {
                 // Si OK
                 this->connected = true;
                 // On attend 2 sec. la réinitialisation de la carte Arduino.
                 Sleep(ARDUINO_WAIT_TIME);
             }
        }
    }

}

Serial::~Serial()
{
    //Verifie si on est bien connecté avant se déconnecter 
    if(this->connected)
    {
        //On se deconnecte
        this->connected = false;
        //On ferme la liaison
        CloseHandle(this->hSerial);
    }
}

int Serial::ReadData(char *buffer, unsigned int nbChar)
{
    //Nombre de bits à lire
    DWORD bitsLu;
    //Nombre de bits qu'on va réellement lire
    unsigned int toRead;

    // ClearCommError permet connaittre l'état de la liaison
    ClearCommError(this->hSerial, &this->errors, &this->status);

    //Vérifier qu'il y a une donnée dans le Buffer
    if(this->status.cbInQue>0)
    {
      
		// On verifie qu'on a bien le nombre de caractères nécéssaires pour lire une donnée sinon on lit le caractère disponible
		//pour éviter le beug du programme
        if(this->status.cbInQue>nbChar)
        {
            toRead = nbChar;
        }
        else
        {
            toRead = this->status.cbInQue;
        }

        //Try to read the require number of chars, and return the number of read bytes on success
        if(ReadFile(this->hSerial, buffer, toRead, &bitsLu, NULL) && bitsLu != 0)
        {
            return bitsLu;
        }

    }

	// si rien n'est lu, on retourne -1.
	return -1;

}


bool Serial::WriteData(char *buffer, unsigned int nbChar)
{
    DWORD bitsEnvoye;

    //On écrit les données du Buffer sur la liaison série
    if(!WriteFile(this->hSerial, (void *)buffer, nbChar, &bitsEnvoye, 0))
    {
        //Dans le cas où ça ne marche pas, on retourne l'erreur et on renvoie false
        ClearCommError(this->hSerial, &this->errors, &this->status);

        return false;
    }
    else
        return true;
}

bool Serial::IsConnected()
{
    // On donne l'état de connetion de la liaison 
    return this->connected;
}