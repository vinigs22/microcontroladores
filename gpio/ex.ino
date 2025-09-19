void setup() {

}

void loop() {
}

// Ex. 1
void ex1() {
  DDRD |= (1 << PD2);
  PORTD |= (1 << PD2);
}

// Ex. 2
void ex2() {
  DDRD |= (1 << PD2);
  PORTD |= (1 << PD2);
  PORTD &= ~(1 << PD2);
}

// Ex. 3
void ex3() {
  DDRD |= (1 << PD3);
  DDRB |= (1 << PB4);

  PORTD ^= (1 << PD3);
  PORTB ^= (1 << PB4);

  delay(500);
}

// Ex. 4
void ex4() {
  DDRD &= ~(1 << PD5);
  PORTD |= (1 << PD5);

  if (PIND & (1 << PD5)) {
  }
}

// Ex. 5
void ex5() {
  DDRD &= ~(1 << PD5);
  PORTD |= (1 << PD5);

  if (PIND & (1 << PD5)) {
    PORTD &= ~(1 << PD5);
  }
}

// Ex. 6
void ex6() {
  DDRD |= (1 << PD6) | (1 << PD7);
  DDRD &= ~(1 << PD6);
}

// Ex. 7
void ex7() {
  DDRD &= ~(1 << PD2);
  DDRD |= (1 << PD3);

  if (PIND & (1 << PD2)) {
    PORTD |= (1 << PD3);
  }
}

// Ex. 8
void ex8() {
  DDRD &= ~(1 << PD2);
  DDRD |= (1 << PD3);

  if (PIND & (1 << PD2)) {
    PORTD &= ~(1 << PD3);
  }
}

// Ex. 9
void ex9() {
  DDRD |= (1 << PD4) | (1 << PD5) | (1 << PD6);
}

// Ex. 10
void ex10() {
  DDRD &= ~(1 << PD0);
  DDRD &= ~(1 << PD1);
  DDRD &= ~(1 << PD2);
  
  if ((DDRD & (1 << PD0)) == 0 && 
      (DDRD & (1 << PD1)) == 0 && 
      (DDRD & (1 << PD2)) == 0) {
  }
}

// Ex. 11
void ex11() {
  DDRD &= ~(1 << PD2);
  PORTD |= (1 << PD2);
  
  DDRD |= (1 << PD3);
  
  static bool botaoAnterior = HIGH;
  bool botaoAtual = (PIND & (1 << PD2)) != 0;
  
  if (botaoAnterior && !botaoAtual) {
    PORTD ^= (1 << PD3);
  }
  
  botaoAnterior = botaoAtual;
}

// Ex. 12
void ex12() {
  DDRD &= ~(1 << PD2);
  PORTD |= (1 << PD2);
  
  DDRD |= (1 << PD3) | (1 << PD4);
  
  static bool botaoAnterior = HIGH;
  bool botaoAtual = (PIND & (1 << PD2)) != 0;
  
  if (botaoAnterior && !botaoAtual) {
    PORTD ^= (1 << PD3);
    PORTD ^= (1 << PD4);
  }
  
  botaoAnterior = botaoAtual;
}

// Ex. 13
void ex13() {
  DDRB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2) | (1 << PB3) | (1 << PB4));
  
  DDRD |= (1 << PD2);
  DDRC |= (1 << PC0);
  
  uint8_t entradas = PINB & 0x1F;
  
  bool intercalado = (entradas == 0b10101) || (entradas == 0b01010);
  
  bool todosIguais = (entradas == 0b00000) || (entradas == 0b11111);
  
  if (intercalado) {
    PORTD |= (1 << PD2);
    PORTC &= ~(1 << PC0);
  } else if (todosIguais) {
    PORTD &= ~(1 << PD2);
    PORTC |= (1 << PC0);
  } else {
    PORTD &= ~(1 << PD2);
    PORTC &= ~(1 << PC0);
  }
}

// Ex. 14
void ex14() {
  DDRB &= ~((1 << PB1) | (1 << PB2) | (1 << PB3) | (1 << PB4));
  PORTB |= (1 << PB1) | (1 << PB2) | (1 << PB3) | (1 << PB4);
  
  DDRD |= (1 << PD3);
  PORTD &= ~(1 << PD3);
  
  static uint8_t sequencia = 0;
  static bool pb2_pressionado = false;
  static bool pb3_pressionado = false;
  static bool pb4_pressionado = false;
  static bool pb1_pressionado = false;
  
  bool pb1 = !(PINB & (1 << PB1));
  bool pb2 = !(PINB & (1 << PB2));
  bool pb3 = !(PINB & (1 << PB3));
  bool pb4 = !(PINB & (1 << PB4));
  
  switch (sequencia) {
    case 0:
      if (pb2 && !pb3 && !pb4 && !pb1) {
        pb2_pressionado = true;
        sequencia = 1;
      } else if (!pb2 && !pb3 && !pb4 && !pb1) {
        pb2_pressionado = pb3_pressionado = pb4_pressionado = pb1_pressionado = false;
      }
      break;
      
    case 1:
      if (pb2 && pb3 && !pb4 && !pb1) {
        pb3_pressionado = true;
        sequencia = 2;
      } else if (!pb2 || pb4 || pb1) {
        sequencia = 0;
        pb2_pressionado = pb3_pressionado = pb4_pressionado = pb1_pressionado = false;
      }
      break;
      
    case 2:
      if (pb2 && pb3 && pb4 && !pb1) {
        pb4_pressionado = true;
        sequencia = 3;
      } else if (!pb2 || !pb3 || pb1) {
        sequencia = 0;
        pb2_pressionado = pb3_pressionado = pb4_pressionado = pb1_pressionado = false;
      }
      break;
      
    case 3:
      if (pb2 && pb3 && pb4 && pb1) {
        pb1_pressionado = true;
        PORTD |= (1 << PD3);
      } else if (!pb2 || !pb3 || !pb4) {
        sequencia = 0;
        pb2_pressionado = pb3_pressionado = pb4_pressionado = pb1_pressionado = false;
        PORTD &= ~(1 << PD3);
      }
      break;
  }
  
  if (!pb1 && !pb2 && !pb3 && !pb4) {
    sequencia = 0;
    pb2_pressionado = pb3_pressionado = pb4_pressionado = pb1_pressionado = false;
    PORTD &= ~(1 << PD3);
  }
}