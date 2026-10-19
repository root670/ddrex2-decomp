/* Discriminator 1: retail's p_anime.c TU CU records its three file-scope statics
 * as local_variable, in declaration order, ahead of its three globals:
 *
 *   local_variable anime_id_tbl
 *   local_variable hold_release
 *   local_variable pre_hold_flag
 *   global_variable g_game_w
 *   global_variable paw_p
 *   global_variable play_anime_w
 *
 * The initializers matter: an uninitialized tentative definition is tagged
 * global_variable once code references it; an initialized one stays local_variable.
 * The function below supplies the references retail's code has (hold_release and
 * pre_hold_flag are read through $gp in play_anime_init/step).
 */
static int anime_id_tbl[11] = {0};
static int hold_release = 0;
static int pre_hold_flag = 0;
int g_game_w = 0;
int *paw_p = 0;
int play_anime_w = 0;

int probe(void) {
    anime_id_tbl[0] = 1;
    hold_release = 1;
    pre_hold_flag = 2;
    paw_p = &g_game_w;
    play_anime_w = 3;
    return hold_release + pre_hold_flag;
}
