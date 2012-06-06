int main(void)
{
	int 
	  Status,			// dabartine sistemos busena 
	  TimeElapsed, 		// kintamajame saugomas laikas iki klaidos
	  WaveSampleRate;	// diskretizavimo daznis
	char WaveFormat;	// WAV bylos formatas
	WavData SoundData;	// Duomenu struktura gautai informacijai laikyti
		
	// Ivyksta UART (RS232) inicializacija
	// Nustatymai: 38400 8n1
	UartInit(UART_BAUD_RATE);
	
	// I2S synos inicializacija 
	// Nustatymai: 400MHz
	I2S_InitHardware();
	
	// Pradedamas sistemis laikmatis, jei jis pasieks 5 s sistema nustos dirbti
	// ir pereis i klaidos rezima
	StartTimerMS();
	
	// Pirmasis ciklas, rysiui su kompiuteriu uzmegzti
	while(1)
	{
		// Jei per UART sasaja atejo laukta pasisveikinimo zinute
		if(UARTgetString()=="START\n") 
		{ 
			// sistemos busena nustatoma kaip pasiruosusi darbui ir ciklas
			// yra uzbaigiamas
			Status=PREPARED; 
			break; 
		}
		else
		{
		    // gaunama dabartine laikmacio reiksme
			TimeElapsed=GetTimeMS();
			// jei po paleidimo praejo 5 s
			if(TimeElapsed>5000) 
			{ 
				// nustatoma klaidos busena ir iseinama is ciklo
				Status=ERROR_STATE; 
				break; 
			}	
		}
	}
	StopTimerMS();
	    while(1)
    {
		// jei klaidos busena - isvedam duomenis atgal i UART'a 
		// ir baigiame programa
        if(Status==ERROR_STATE) 
        { 
        	UartPuts("Error getting handshake!\r\nStopping!\r\n");
        	break; 
        }
		// jei busena teisinga, tesiam darba, nuskaitant pagrindine 
		// WAV bylos informacija ir keiciame busena i "darbas"
		if(Status==PREPARED) 
		{ 
			WaveFormat=GetWaveFormat(); 
			WaveSampleRate=GetWaveSampleRate(); 
			Status=WORKING; 
		}
		// jei busena - "darbas"
		if(Status==WORKING)
		{
			// gauname duomenu paketa su informacija apie garso saltinio
			// pozicija, davikliu duomenimis ir garso takeliu.
			// duomenis irasome i struktura.
			SoundData = GetPacket(NUMBER_OF_SAMPLES);
			
			// su gautu duomenu paketu atliekame garso pakeitimus,
			// pagal pozicija pasirenkame HRTF derini, atliekame KIA 
			// skaiciavima sasukos budu suliejame viska su gautu garso
			// takeliu ir graziname nauja struktura 
			SoundData = CalculateSoundChange(SoundData);
			
			// siunciame duomenis i SAK.
			// kadangi SoundData strukturoje garso takelio kanalu duomenis
			// saugomi atskirai, o i SAK reikia nusiusti jau viena duomenu
			// masyva, tad naudojame savo pasirasyta funkcija MixChannels,
			// kuri atgal grazina viena duomenu masyva 
			// NUMBER_OF_SAMPLES * 2 ilgio
			UpdateDAC(MixChannels(SoundData), WaveFormat, WaveSampleRate);
		}			
    }
	
	return 0;
}