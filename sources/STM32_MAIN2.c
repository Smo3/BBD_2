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