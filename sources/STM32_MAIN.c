int main(void)
{
	int 
	  Status,			// dabartin� sistemos b�sena 
	  TimeElapsed, 		// kintamajame saugomas laikas iki klaidos
	  WaveSampleRate;	// diskretizavimo da�nis
	char WaveFormat;	// WAV bylos formatas
	
	WavData SoundData;	// Duomenu strukt�ra gautai informacijai laikyti
	
	
	// �vyksta UART (RS232) inicializacija
	// Nustatymai: 38400 8n1
	UartInit(UART_BAUD_RATE);
	
	// I2S �ynos inicializacija 
	// Nustatymai: 400MHz
	I2S_InitHardware();
	
	// Pradedamas sistemis laikmatis, jei jis pasieks 5 s sistema nustos dirbti ir pereis � klaidos re�im�
	StartTimerMS();
	
	// Pirmasis ciklas, ry�iui su kompiuteriu u�megzti
	while(1)
	{
		// Jei per UART s�saja at�jo laukta pasisveikinimo �inut�
		if(UARTgetString()=="START\n") 
		{ 
			// sistemos b�sena nustatoma kaip pasiruo�usi darbui ir ciklas yra u�baigiamas
			Status=PREPARED; 
			break; 
		}
		else
		{
		    // gaunama dabartin� laikma�io reik�m�
			TimeElapsed=GetTimeMS();
			// jei po paleidimo pra�jo 5 s
			if(TimeElapsed>5000) 
			{ 
				// nustatoma klaidos b�sena ir i�einama i� ciklo
				Status=ERROR_STATE; 
				break; 
			}	
		}
	}
	
	//
	StopTimerMS();
	
    while(1)
    {
		// jei klaidos b�sena - i�vedam duomenis atgal � UART'� ir baigiame program�
        if(Status==ERROR_STATE) { UartPuts("Error getting handshake!\r\nStopping program!\r\n"); break; }
		// jei b�sena teisinga, t�siam darb�, nuskaitant pagrindin� WAV bylos informacij� ir kei�iame b�sena � "darbas"
		if(Status==PREPARED) { WaveFormat=GetWaveFormat(); WaveSampleRate=GetWaveSampleRate(); Status=WORKING; }
		// jei b�sena - "darbas"
		if(Status==WORKING)
		{
			// gauname duomen� paket� su informacija apie garso �altinio pozicij�, davikli� duomenimis ir garso takeliu.
			// duomenis �ra�ome � strukt�r�.
			SoundData = GetPacket(NUMBER_OF_SAMPLES);
			
			// su gautu duomen� paketu atliekame garso pakeitimus,
			// pagal pozicij� pasirenkame HRTF derin�, atliekame KIA skai�iavim�
			// s�sukos b�du suliejame visk� su gautu garso takeliu ir gr��iname nauj� strukt�r� 
			SoundData = CalculateSoundChange(SoundData);
			
			// siun�iame duomenis � SAK.
			// kadangi SoundData strukt�roje garso takelio kanal� duomenis saugomi atskirai, o � SAK reikia nusi�sti
			// jau vien� duomen� masyv�, tad naudojame savo pasira�yt� funkcij� MixChannels, kuri atgal gr��ina vien� duomen� masyv�
			// NUMBER_OF_SAMPLES * 2 ilgio
			UpdateDAC(MixChannels(SoundData), WaveFormat, WaveSampleRate);
		}			
    }
	
	return 0;
}