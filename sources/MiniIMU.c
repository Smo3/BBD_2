int main(void)
{
	// inializuojam pagrindinius kintamuosius
	int8_t ret1,ret2,status;
	int16_t acc_x,acc_y,acc_z;
	int16_t mag_x,mag_y,mag_z;
	int16_t gyro_x,gyro_y,gyro_z;
	int16_t ret;
	int16_t temperature;
	char buffer[100];
	
	// inicializuojami reikia davikliams iðëjimai
	DDRB=0xFF;
	PORTB=0xFF;
	
	// ájungiame globalias pertrauktis
	sei();

	// inicializuojam UART (RS232)
	uart_init( UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU) );
	
	// inicializuojam I2C
	i2c_init();
	
	// saugumo sumetimais palaukiame 1 s.
	_delay_ms(1000);
	
	// inicializuojam daviklius
	Init_MAG();
	Init_ACC();
	Init_GYRO();
	
	// saugumo sumetimais palaukiame 2 s.
	_delay_ms(2000);

	// tikrinimas ar davikliai veikia
	ret1 = Read_I2C_Reg(GYRO_ADR,0x0f);
	sprintf(buffer,"GYRO: 0x%2.2x\r\n",ret1);                                                   ");
	
	ret=Read_I2C_Reg(ACC_ADR,0x20);
	sprintf(buffer,"ACC: 0x%2.2x\r\n",ret);
	
	ret=Read_I2C_Reg(MAG_ADR,0x21);
	sprintf(buffer,"MAG: 0x%2.2x\r\n",ret);
                                                   ");

    char c;
	while(1)
    {
		{
			
			// ciklas sukasi tol kol daviklis nepasiruoðæs perduoti duomenø 
			while(!(ret1=Read_I2C_Reg(ACC_ADR,ACC_STATUS) && (ACC_READY))){};
			// nuskaitomi visi daviklio duomenys
			ret1 = Read_I2C_Reg(ACC_ADR,X_L_A);
			ret2 = Read_I2C_Reg(ACC_ADR,X_H_A);
			acc_x = Fix_Value(ret1,ret2);
			ret1 = Read_I2C_Reg(ACC_ADR,Y_L_A);
			ret2 = Read_I2C_Reg(ACC_ADR,Y_H_A);
			acc_y = Fix_Value(ret1,ret2);
			ret1 = Read_I2C_Reg(ACC_ADR,Z_L_A);
			ret2 = Read_I2C_Reg(ACC_ADR,Z_H_A);
			acc_z = Fix_Value(ret1,ret2);
				
			// ciklas sukasi tol kol daviklis nepasiruoðæs perduoti duomenø
			while(!(ret1=Read_I2C_Reg(MAG_ADR,MAG_STATUS) && (MAG_READY))){};
			// nuskaitomi visi daviklio duomenys
			ret1 = Read_I2C_Reg(MAG_ADR,X_L_M);
			ret2 = Read_I2C_Reg(MAG_ADR,X_H_M);
			mag_x = Fix_Value(ret1,ret2);
			ret1 = Read_I2C_Reg(MAG_ADR,Y_L_M);
			ret2 = Read_I2C_Reg(MAG_ADR,Y_H_M);
			mag_y = Fix_Value(ret1,ret2);
			ret1 = Read_I2C_Reg(MAG_ADR,Z_L_M);
			ret2 = Read_I2C_Reg(MAG_ADR,Z_H_M);
			mag_z = Fix_Value(ret1,ret2);
				
			// ciklas sukasi tol kol daviklis nepasiruoðæs perduoti duomenø
			while(!(ret1=Read_I2C_Reg(GYRO_ADR,GYRO_STATUS) && (GYRO_READY))){};
			// nuskaitomi visi daviklio duomenys
			ret1 = Read_I2C_Reg(GYRO_ADR,X_L_G);
			ret2 = Read_I2C_Reg(GYRO_ADR,X_H_G);
			gyro_x = Fix_Value(ret1,ret2);
			ret1 = Read_I2C_Reg(GYRO_ADR,Y_L_G);
			ret2 = Read_I2C_Reg(GYRO_ADR,Y_H_G);
			gyro_y = Fix_Value(ret1,ret2);
			ret1 = Read_I2C_Reg(GYRO_ADR,Z_L_G);
			ret2 = Read_I2C_Reg(GYRO_ADR,Z_H_G);
			gyro_z = Fix_Value(ret1,ret2);
				
			temperature = Read_I2C_Reg(GYRO_ADR,TEMP);
		
			// formuojamas duomenø paketas
			sprintf(buffer,"%d %d %d %d %d %d %d %d %d %d\r\n\0",temperature, gyro_x, gyro_y, gyro_z, mag_x, mag_y, mag_z, acc_x, acc_y, acc_z);
		
			// duomenis isunèiamu UART sàsaja atgal á kità irenginá
			uart_puts(buffer);
		}					
		_delay_ms(SEND_TIMEOUT-2);		
    
    }
}