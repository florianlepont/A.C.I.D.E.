#include  "..\..\include\extern\liaisonSerie.h"

Serial::Serial(char *portName)
{
    //We're not yet connected
    this->connected = false;

    //On cr�e notre objet Handle
    this->hSerial = CreateFile(portName,
            GENERIC_READ | GENERIC_WRITE,
            0,
            NULL,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            NULL);

    //On v�rifie si la connexuion est bien effectu�e et si non...
    if(this->hSerial==INVALID_HANDLE_VALUE)
    {
        //On recherche la derni�re erreur et on l'affiche
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
        // ON initialise les param�tres de connection
        DCB parametredcb = {0};

        //On recherche les param�tres actuels de connection

        if (!GetCommState(this->hSerial, &parametredcb))
        {
            //Si impossible, envoyer erreur
            printf("failed to get current serial parameters!");
        }
        else
        {
            //On modifie les param�tres.
            parametredcb.BaudRate=CBR_9600;
            parametredcb.ByteSize=8;
            parametredcb.StopBits=ONESTOPBIT;
            parametredcb.Parity=NOPARITY;

             //On envoie les param�tres � la liaison s�rie et on v�rifie leur bonne utilisation.
             if(!SetCommState(hSerial, &parametredcb))
             {// Si il y'a une erreur
                printf("ALERT: Could not set Serial Port parameters");
             }
             else
             {
                 // Si OK
                 this->connected = true;
                 // On attend 2 sec. la r�initialisation de la carte Arduino.
                 Sleep(ARDUINO_WAIT_TIME);
             }
        }
    }

}

Serial::~Serial()
{
    //Verifie si on est bien connect� avant se d�connecter 
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
    //Nombre de bits � lire
    DWORD bitsLu;
    //Nombre de bits qu'on va r�ellement lire
    unsigned int toRead;

    // ClearCommError permet connaittre l'�tat de la liaison
    ClearCommError(this->hSerial, &this->errors, &this->status);

    //V�rifier qu'il y a une donn�e dans le Buffer
    if(this->status.cbInQue>0)
    {
      
		// On verifie qu'on a bien le nombre de caract�res n�c�ssaires pour lire une donn�e sinon on lit le caract�re disponible
		//pour �viter le beug du programme
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

    //On �crit les donn�es du Buffer sur la liaison s�rie
    if(!WriteFile(this->hSerial, (void *)buffer, nbChar, &bitsEnvoye, 0))
    {
        //Dans le cas o� �a ne marche pas, on retourne l'erreur et on renvoie false
        ClearCommError(this->hSerial, &this->errors, &this->status);

        return false;
    }
    else
        return true;
}

bool Serial::IsConnected()
{
    // On donne l'�tat de connetion de la liaison 
    return this->connected;
}