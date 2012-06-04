int main(void)
{
	int 
	  Status,			// dabartinë sistemos bûsena 
	  TimeElapsed, 		// kintamajame saugomas laikas iki klaidos
	  WaveSampleRate;	// diskretizavimo daþnis
	char WaveFormat;	// WAV bylos formatas
	
	WavData SoundData;	// Duomenu struktûra gautai informacijai laikyti
	
	
	// Ávyksta UART (RS232) inicializacija
	// Nustatymai: 38400 8n1
	UartInit(UART_BAUD_RATE);
	
	// I2S ðynos inicializacija 
	// Nustatymai: 400MHz
	I2S_InitHardware();
	
	// Pradedamas sistemis laikmatis, jei jis pasieks 5 s sistema nustos dirbti ir pereis á klaidos reþimà
	StartTimerMS();
	
	// Pirmasis ciklas, ryðiui su kompiuteriu uþmegzti
	while(1)
	{
		// Jei per UART sàsaja atëjo laukta pasisveikinimo þinutë
		if(UARTgetString()=="START\n") 
		{ 
			// sistemos bûsena nustatoma kaip pasiruoðusi darbui ir ciklas yra uþbaigiamas
			Status=PREPARED; 
			break; 
		}
		else
		{
		    // gaunama dabartinë laikmaèio reikðmë
			TimeElapsed=GetTimeMS();
			// jei po paleidimo praëjo 5 s
			if(TimeElapsed>5000) 
			{ 
				// nustatoma klaidos bûsena ir iðeinama ið ciklo
				Status=ERROR_STATE; 
				break; 
			}	
		}
	}
	
	//
	StopTimerMS();
	
    while(1)
    {
		// jei klaidos bûsena - iðvedam duomenis atgal á UART'à ir baigiame programà
        if(Status==ERROR_STATE) { UartPuts("Error getting handshake!\r\nStopping program!\r\n"); break; }
		// jei bûsena teisinga, tæsiam darbà, nuskaitant pagrindinæ WAV bylos informacijà ir keièiame bûsena á "darbas"
		if(Status==PREPARED) { WaveFormat=GetWaveFormat(); WaveSampleRate=GetWaveSampleRate(); Status=WORKING; }
		// jei bûsena - "darbas"
		if(Status==WORKING)
		{
			// gauname duomenø paketà su informacija apie garso ðaltinio pozicijà, davikliø duomenimis ir garso takeliu.
			// duomenis áraðome á struktûrà.
			SoundData = GetPacket(NUMBER_OF_SAMPLES);
			
			// su gautu duomenø paketu atliekame garso pakeitimus,
			// pagal pozicijà pasirenkame HRTF deriná, atliekame KIA skaièiavimà
			// sàsukos bûdu suliejame viskà su gautu garso takeliu ir gràþiname naujà struktûrà 
			SoundData = CalculateSoundChange(SoundData);
			
			// siunèiame duomenis á SAK.
			// kadangi SoundData struktûroje garso takelio kanalø duomenis saugomi atskirai, o á SAK reikia nusiøsti
			// jau vienà duomenø masyvà, tad naudojame savo pasiraðytà funkcijà MixChannels, kuri atgal gràþina vienà duomenø masyvà
			// NUMBER_OF_SAMPLES * 2 ilgio
			UpdateDAC(MixChannels(SoundData), WaveFormat, WaveSampleRate);
		}			
    }
	
	return 0;
}