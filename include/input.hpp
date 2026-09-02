/**
 * @file input.hpp
 * @brief Declaração da classe input, que gerencia os input de entrada.
 */
#ifndef INPUT_H
#define INPUT_H

#include <allegro5/allegro.h>

/**
 * @class input
 * @brief Gerencia os comandos de entrada do usuário, de teclado e mouse.
 */
class input {

private:

    bool jumpInput;     /// Estado do input de pulo (jump).
    bool quitInput;     /// Estado do input de saída (quit).
    bool pauseInput;    /// Estado do input de pausa (pause).

public:
    
    /**
     * @brief Construtor padrão da classe input.
     */
    input();
    ~input();

    /**
     * @brief Obtém o estado do input de pulo.
     * @return true se o input de pulo estiver ativo, false caso contrário.
     */
    bool getJumpInput() const;
    /**
     * @brief Obtém o estado do input de saída.
     * @return true se o input de saída estiver ativo, false caso contrário.
     */
    bool getQuitInput() const;
    /**
     * @brief Obtém o estado do input de pausa.
     * @return true se o input de pausa estiver ativo, false caso contrário.
     */
    bool getPauseInput() const;

    /**
     * @brief Reseta o estado do input de pulo para false.
     */
    void ResetJumpState();

    /**
     * @brief Processa o evento de input.
     * @param event input a ser processado.
     */
    void InputEvent(const ALLEGRO_EVENT &event);
   
};

#endif