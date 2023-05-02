/** @file
 *
 * @brief This header contains instructions and related functions.
 */

#ifndef EVM_COMMON_INSTRUCTION_H_
#define EVM_COMMON_INSTRUCTION_H_

#include "loading.h"
#include <cstdint>

namespace evm
{

/**
 * @brief An Operation Code (opcode).
 * This is currently a stub.
 */
enum class opcode : uint8_t
{
  /**
   * @brief @c nop No operation.
   */
  nop,
};

/**
 * @brief The different 'kinds' of instructions, organised by the arguments
 * they take.
 */
enum class instruction_kind : uint8_t
{
  /**
   * @brief A lonely argument, that takes no arguments.
   */
  lonely // TODO: add more
};

/**
 * @brief Instruction arguments as a union.
 * For each argument kind there is a corresponding @c instruction_kind.
 */
union instruction_args
{
  /**
   * @brief Lonely arguments.
   */
  struct
  {
  } lonely;

  static instruction_args load (instruction_kind kind, const uint8_t *buff);
  static instruction_args load (opcode opcode, const uint8_t *buff);
  static void save (const instruction_args &args, instruction_kind kind,
                    uint8_t *buff);
  static void save (const instruction_args &args, opcode opcode,
                    uint8_t *buff);
};

/**
 * @brief An instruction. Has an @c opcode, and @c instruction_args.
 */
struct instruction
{
  /**
   * @brief The opcode of the instruction.
   */
  opcode code;
  /**
   * @brief The arguments of the instruction.
   */
  instruction_args args;

  static instruction load (const uint8_t *buffer);
  /**
   * @brief Unimplemented
   */
  static void save (const instruction &instr, uint8_t *buff);
  /**
   * @brief Unimplemented
   */
  static ls_info<instruction> get_ls_info ();
};

/**
 * @brief Loads and opcode from the given buffer.
 * @param buffer Buffer to load from.
 */
opcode load_opcode (const uint8_t *buffer);
/**
 * @brief Saves the opcode into the given buffer.
 * @param Opcode to save.
 * @param Buffer to save into.
 */
void save_opcode (const opcode &opcode, uint8_t *buffer);
/**
 * @brief Gets the 'kind' (@c instruction_kind) of the given opcode.
 */
instruction_kind opcode_kind (opcode opcode);
/**
 * @brief The load save info (@c ls_info) for opcode.
 */
ls_info<opcode> opcode_ls_info ();

} // evm

#endif // EVM_COMMON_INSTRUCTION_H_
