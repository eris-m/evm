#include <evm/instruction.h>

namespace evm
{

instruction_args
instruction_args::load (instruction_kind kind, const uint8_t *buffer)
{
  instruction_args args;

  switch (kind)
    {
    case instruction_kind::lonely:
      args.lonely = {};
    }

  return args;
}

instruction_args
instruction_args::load (opcode code, const uint8_t *buffer)
{
  return load (opcode_kind (code), buffer);
}

void
instruction_args::save (const instruction_args &args, instruction_kind kind,
                        uint8_t *buffer)
{
  switch (kind)
    {
    case instruction_kind::lonely:
      return;
    }
}

void
instruction_args::save (const instruction_args &args, opcode code,
                        uint8_t *buffer)
{
  save (args, opcode_kind (code), buffer);
}

instruction
instruction::load (const uint8_t *buffer)
{
  auto opcode = load_opcode (buffer);
  buffer++;
  auto args = instruction_args::load (opcode, buffer);

  return instruction{
    .code = opcode,
    .args = args,
  };
}

static uint64_t
opcode_ld_size (const uint8_t *)
{
  return sizeof (opcode);
}

static uint64_t
opcode_st_size (const opcode &)
{
  return sizeof (opcode);
}

opcode
load_opcode (const uint8_t *buffer)
{
  auto byte = buffer[0];
  return static_cast<opcode> (byte);
}

void
save_opcode (const opcode &self, uint8_t *buffer)
{
  auto byte = static_cast<uint8_t> (self);
  buffer[0] = byte;
}

instruction_kind
opcode_kind (opcode opcode)
{
  switch (opcode)
    {
    case opcode::nop:
      return instruction_kind::lonely;
    };
  return instruction_kind::lonely;
}

ls_info<opcode>
opcode_ls_info ()
{
  return ls_info<opcode>{ .load_size = opcode_ld_size,
                          .save_size = opcode_st_size,
                          .load = load_opcode,
                          .save = save_opcode };
}

} // evm
