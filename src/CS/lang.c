/* src/CS/lang.c -- the message-language tables and the accessor the rest of the game calls.
 *
 * Reconstructed from orig/SLUS_211.74: the DWARF 1 records for this file (rendered into
 * include/src/CS/lang.h) plus mesGetLanguage01's disassembly.  The statement line numbers
 * are evidence too -- the promotion rule compares this file's .line bytes with retail -- so
 * nothing is re-wrapped away from the retail lines 118-119, 121-122, 127 and 128.
 *
 * Promoted under `3.0b38-030307 -c -lang c -O3 -opt full -g --adopt-retail-meta`, the pair
 * its tu_builds row records.  Measured through the promotion path (`place()` + `compare()`)
 * against retail's own pinned chunks -- the same bytes the gate compares:
 *
 *  - `.text` is retail's: 0x50 bytes (the 0x44-byte function plus 0xC of the split's trailing
 *    nop padding, filled from retail), every word byte-equal -- schedule and delay slots too.
 *  - `.line` is retail's 0x4E bytes, all seven records (118, 119, 121, 122, 127, 128 and the
 *    end of the table) byte-equal; the two one-line `if`s below are the shape that gives each
 *    clamp store a line of its own.
 *  - `.debug` is retail's 0x43E bytes / 24 DIEs.  Emitted, it is set-equal and not byte-equal:
 *    45 bytes differ, first at +0x55, and they are the array-DIE order and the references that
 *    follow from it.  The DIE sequence at those offsets is the same nine `array_type` records
 *    in a different order: retail's is JAPANESE, mesLanguage, SPANISH, ITALIAN, GERMAN,
 *    FRENCH, ENGLISH, CANCEL, OK, ours is mesLanguage, ENGLISH, ITALIAN, OK, FRENCH, SPANISH,
 *    JAPANESE, CANCEL, GERMAN.  Eight are the same 0x27-byte `unsigned char *[6]` record; the
 *    one distinct 0x28 (`mesLanguage`'s `**[6]`) shows the swap at +0x1E9/+0x210, and the
 *    rest is the sibling offsets and each variable's `AT_user_def_type` word that follow.  The
 *    array-DIE order is the compiler's type table, which no declaration order controls.
 *
 * `--adopt-retail-meta` closes it, strictly: it re-emits our DIEs in retail's sequence and
 * repairs only references between structurally identical DIEs (measured: 0 of 7 `.line` rows
 * changed, 8 reference words rewritten), then requires retail's bytes -- which it gets.  The
 * step is on this unit's `cc` edge, so a chunk that stops coming out retail's fails the build.
 *
 * The nine tables are file-scope statics: CodeWarrior writes their DIEs as locals with a
 * location, and two of them (`mesLanguageOK`, `mesLanguageCANCEL`) carry address 0 in retail
 * -- declared but never allocated, which is why they are in config/ddrex2p/unplaced_symbols.txt
 * and not in this target's split.  The `= { 0 }` initializers are not retail's values: what
 * the tables contain lives in retail's `.data`, which this build does not reconstruct yet
 * (rule 9), and a promoted unit links only its `.text`. */

static unsigned char *mesLanguageJAPANESE[6] = { 0 };
static unsigned char *mesLanguageENGLISH[6] = { 0 };
static unsigned char *mesLanguageFRENCH[6] = { 0 };
static unsigned char *mesLanguageGERMAN[6] = { 0 };
static unsigned char *mesLanguageITALIAN[6] = { 0 };
static unsigned char *mesLanguageSPANISH[6] = { 0 };
static unsigned char **mesLanguage[6] = { 0 };
static unsigned char *mesLanguageOK[6] = { 0 };
static unsigned char *mesLanguageCANCEL[6] = { 0 };

                                                                               
                                                                                      
                                                                           
  
                                                                                     
                                                                 
                                                                                        
                                                                                  
                                                                           
                                                           
                                                                     
                                          
                                                                                         
                                                                                      
                              
                                                                                          
                                                             
                                                                                            
                                                                           
  
                                                                             
                                                                                            
                                                                                     
                                                                                           
                                                                                      
                                  
  
                                                                                   
                                                                                           
                                                                                             
                                                                                             
                                                                                           
                                                                                          
                                                                                      
  
                                               
                                               
                                               
                                               
                                               
                                               
                                               
                                               
                                               
                                               
                                              
                                               
                                               
                                               
                                               
                                               
                                               
  
                                                                                           
                                                                                       
                                                                                             
                                                                                            
                                                                                            
                                                                                         
                                                                                            
                                                                                             
                                                 
  
                                                                                      
                                                                                          


unsigned char *mesGetLanguage01(int id0, int id1)
{
    if (id0 >= 7)
        id0 = 2;

    if (id1 >= 7)
        id1 = 2;
                                                                                        
                                                                                      
                                                                                            
                                                                                           
    return mesLanguage[id1][id0];
}
