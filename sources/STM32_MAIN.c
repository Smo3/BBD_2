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