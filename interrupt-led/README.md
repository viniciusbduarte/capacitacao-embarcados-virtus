## 📦 Acionando LED a partir de uma Interrupção

---

## 🔔 O que são interrupções?

Interrupções são mecanismos de hardware que permitem ao microcontrolador **interromper o fluxo normal de execução do programa** para atender a um evento específico (por exemplo, a mudança de estado de um pino).

Principais características no AVR:

* **Vetorizadas**: cada interrupção possui um endereço fixo na memória (vetor de interrupção).
* **Mascaráveis**: podem ser habilitadas ou desabilitadas via registradores de controle.
* **Prioridade fixa**: definida pela posição do vetor na tabela de interrupções.

---

## 🧠 Interrupções no AVR

No AVR:

* O **bit I (bit 7)** do registrador **SREG** controla a habilitação global das interrupções.

  * `I = 1` → interrupções habilitadas
  * `I = 0` → interrupções desabilitadas

Isso pode ser feito via:

```c
sei(); // habilita interrupções globais
cli(); // desabilita interrupções globais
```

🔒 **Interrupções aninhadas não ocorrem por padrão**, pois ao entrar em uma ISR o bit I do SREG é automaticamente limpo. Para permitir aninhamento, seria necessário reabilitar manualmente as interrupções dentro da ISR (não recomendado para iniciantes).

---

## 🧭 Vetores de interrupção no AVR-GCC

No compilador **AVR-GCC**, a tabela de vetores já é definida, e cada interrupção possui um **nome padrão**.

As interrupções são escritas como **funções especiais**, chamadas de **ISR (Interrupt Service Routine)**.

Exemplo de declaração:

```c
ISR(INT0_vect) {
    // código da interrupção
}
```

---

## ⚡ Interrupções externas disponíveis

| Endereço | Fonte  | Definição             | Descrição                                                |
| -------- | ------ | --------------------- | -------------------------------------------------------- |
| 0x01     | INT0   | Interrupção externa 0 | Borda de subida, descida ou nível lógico no pino **PD2** |
| 0x02     | INT1   | Interrupção externa 1 | Borda de subida, descida ou nível lógico no pino **PD3** |
| 0x03     | PCINT0 | Mudança de pino       | Qualquer mudança nos pinos da **porta B**                |
| 0x04     | PCINT1 | Mudança de pino       | Qualquer mudança nos pinos da **porta C**                |
| 0x05     | PCINT2 | Mudança de pino       | Qualquer mudança nos pinos da **porta D**                |

---

## 🧩 Registradores envolvidos

### 📌 EICRA – External Interrupt Control Register A

Define o tipo de acionamento das interrupções INT0 e INT1.

| ISC01 | ISC00 | INT0                 |
| ----- | ----- | -------------------- |
| 0     | 0     | Nível baixo          |
| 0     | 1     | Qualquer mudança     |
| 1     | 0     | **Borda de descida** |
| 1     | 1     | Borda de subida      |

---

### 📌 EIMSK – External Interrupt Mask Register

Habilita ou desabilita interrupções externas individuais.

* Bit 0 → INT0
* Bit 1 → INT1

---

### 📌 EIFR – External Interrupt Flag Register

Indica se uma interrupção externa ocorreu.
O flag é limpo escrevendo **1** no bit correspondente.

---

### 📌 PCICR – Pin Change Interrupt Control Register

Habilita interrupções por mudança de pino (PCINT).

---

### 📌 PCIFR – Pin Change Interrupt Flag Register

Flags das interrupções por mudança de pino.

---

### 📌 PCMSKx – Pin Change Mask Register

Seleciona quais pinos dentro da porta irão gerar interrupção.

---

## 💡 Exemplo prático

### Objetivo

Acionar um **LED conectado ao pino PC2** sempre que ocorrer uma **borda de descida no pino PD2 (INT0)**.

---

### 🔌 Esquema do circuito

<p align="center">
  <img 
    src="https://raw.githubusercontent.com/viniciusbduarte/capacitacao-embarcados-virtus/main/interrupt-led/circuito.PNG"
    width="100%"
  />
</p>

---

### 🧾 Código-fonte

```c
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

// Rotina de interrupção da INT0
ISR(INT0_vect);

int main(void)
{
    // Configuração dos GPIOs
    DDRD &= ~(1 << 2);   // PD2 como entrada (INT0)
    DDRC |=  (1 << 2);   // PC2 como saída (LED)
    PORTD |= (1 << 2);   // Pull-up habilitado em PD2

    // Configuração da interrupção externa
    EICRA = (1 << ISC01); // INT0 em borda de descida   
    EIMSK = (1 << INT0);  // Habilita INT0

    sei(); // Habilita interrupções globais

    while (1)
    {
        // Loop principal vazio
    }
}

// ISR: alterna o estado do LED
ISR(INT0_vect)
{
    PORTC ^= (1 << 2);
}
```

---

## 📊 Análise no osciloscópio

O sinal abaixo mostra o **pino PC2 alternando de estado** sempre que ocorre uma **borda de descida no pino PD2**, comprovando o funcionamento correto da interrupção externa.

<p align="center">
  <img 
    src="https://raw.githubusercontent.com/viniciusbduarte/capacitacao-embarcados-virtus/main/interrupt-led/analizer.PNG"
    width="100%"
  />
</p>

---
