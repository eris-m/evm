/// Loadable trait.
/// Represents types that can be loaded from a `&[u8]` buffer.
pub trait Loadable {
    /// Load from given buffer.
    fn load(buffer: &[u8]) -> Self;
    /// The size of the loaded type.
    fn load_size(buffer: &[u8]) -> usize;
}

/// Savable trait.
/// Represents types that can be saved intoa `&[u8]` buffer.
pub trait Savable {
    /// Saves the value into the buffer.
    fn save(&self, buffer: &mut [u8]);
    /// The size of the value that would be saved.
    fn save_size(&self) -> usize;
}

macro_rules! ls_le_bytes {
    ($($t: ty),*) => {
        $(
            impl Loadable for $t {
                fn load(buffer: &[u8]) -> Self {
                    let buffer = buffer.try_into().unwrap(); //FIXME: unwrap.
                    Self::from_le_bytes(buffer)
                }

                fn load_size(_buffer: &[u8]) -> usize {
                    std::mem::size_of::<$t>()
                }
            }
    
            impl Savable for $t {
                fn save(&self, buffer: &mut [u8]) {
                    let bytes = Self::to_le_bytes(*self);

                    buffer[0..bytes.len()].copy_from_slice(&bytes);
                }

                fn save_size(&self) -> usize {
                    std::mem::size_of::<$t>()
                }
            }
        )*
    };
}

ls_le_bytes!(u8, u16, u32, u64, i8, i16, i32, i64, f32, f64);