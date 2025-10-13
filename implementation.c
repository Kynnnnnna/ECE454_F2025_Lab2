#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "utilities.h"                // DO NOT REMOVE this line
#include "implementation_reference.h" // DO NOT REMOVE this line

/***********************************************************************************************************************
 * @param buffer_frame - pointer pointing to a buffer storing the imported 24-bit bitmap image
 * @param width - width of the imported 24-bit bitmap image
 * @param height - height of the imported 24-bit bitmap image
 * @param offset - number of pixels to shift the object in bitmap image up
 * @return - pointer pointing a buffer storing a modified 24-bit bitmap image
 * Note1: White pixels RGB(255,255,255) are treated as background. Object in the image refers to non-white pixels.
 * Note2: You can assume the object will never be moved off the screen
 **********************************************************************************************************************/
unsigned char *processMoveUp(unsigned char *buffer_frame, unsigned width, unsigned height, int offset)
{
    return processMoveUpReference(buffer_frame, width, height, offset);
}

/***********************************************************************************************************************
 * @param buffer_frame - pointer pointing to a buffer storing the imported 24-bit bitmap image
 * @param width - width of the imported 24-bit bitmap image
 * @param height - height of the imported 24-bit bitmap image
 * @param offset - number of pixels to shift the object in bitmap image left
 * @return - pointer pointing a buffer storing a modified 24-bit bitmap image
 * Note1: White pixels RGB(255,255,255) are treated as background. Object in the image refers to non-white pixels.
 * Note2: You can assume the object will never be moved off the screen
 **********************************************************************************************************************/
unsigned char *processMoveRight(unsigned char *buffer_frame, unsigned width, unsigned height, int offset)
{
    return processMoveRightReference(buffer_frame, width, height, offset);
}

/***********************************************************************************************************************
 * @param buffer_frame - pointer pointing to a buffer storing the imported 24-bit bitmap image
 * @param width - width of the imported 24-bit bitmap image
 * @param height - height of the imported 24-bit bitmap image
 * @param offset - number of pixels to shift the object in bitmap image up
 * @return - pointer pointing a buffer storing a modified 24-bit bitmap image
 * Note1: White pixels RGB(255,255,255) are treated as background. Object in the image refers to non-white pixels.
 * Note2: You can assume the object will never be moved off the screen
 **********************************************************************************************************************/
unsigned char *processMoveDown(unsigned char *buffer_frame, unsigned width, unsigned height, int offset)
{
    return processMoveDownReference(buffer_frame, width, height, offset);
}

/***********************************************************************************************************************
 * @param buffer_frame - pointer pointing to a buffer storing the imported 24-bit bitmap image
 * @param width - width of the imported 24-bit bitmap image
 * @param height - height of the imported 24-bit bitmap image
 * @param offset - number of pixels to shift the object in bitmap image right
 * @return - pointer pointing a buffer storing a modified 24-bit bitmap image
 * Note1: White pixels RGB(255,255,255) are treated as background. Object in the image refers to non-white pixels.
 * Note2: You can assume the object will never be moved off the screen
 **********************************************************************************************************************/
unsigned char *processMoveLeft(unsigned char *buffer_frame, unsigned width, unsigned height, int offset)
{
    return processMoveLeftReference(buffer_frame, width, height, offset);
}

/***********************************************************************************************************************
 * @param buffer_frame - pointer pointing to a buffer storing the imported 24-bit bitmap image
 * @param width - width of the imported 24-bit bitmap image
 * @param height - height of the imported 24-bit bitmap image
 * @param rotate_iteration - rotate object inside frame buffer clockwise by 90 degrees, <iteration> times
 * @return - pointer pointing a buffer storing a modified 24-bit bitmap image
 * Note: You can assume the frame will always be square and you will be rotating the entire image
 **********************************************************************************************************************/
unsigned char *processRotateCW(unsigned char *buffer_frame, unsigned width, unsigned height,
                               int rotate_iteration)
{
    return processRotateCWReference(buffer_frame, width, height, rotate_iteration);
}

/***********************************************************************************************************************
 * @param buffer_frame - pointer pointing to a buffer storing the imported 24-bit bitmap image
 * @param width - width of the imported 24-bit bitmap image
 * @param height - height of the imported 24-bit bitmap image
 * @param rotate_iteration - rotate object inside frame buffer counter clockwise by 90 degrees, <iteration> times
 * @return - pointer pointing a buffer storing a modified 24-bit bitmap image
 * Note: You can assume the frame will always be square and you will be rotating the entire image
 **********************************************************************************************************************/
unsigned char *processRotateCCW(unsigned char *buffer_frame, unsigned width, unsigned height,
                                int rotate_iteration)
{
    return processRotateCCWReference(buffer_frame, width, height, rotate_iteration);
}

/***********************************************************************************************************************
 * @param buffer_frame - pointer pointing to a buffer storing the imported 24-bit bitmap image
 * @param width - width of the imported 24-bit bitmap image
 * @param height - height of the imported 24-bit bitmap image
 * @param _unused - this field is unused
 * @return
 **********************************************************************************************************************/
unsigned char *processMirrorX(unsigned char *buffer_frame, unsigned int width, unsigned int height, int _unused)
{
    return processMirrorXReference(buffer_frame, width, height, _unused);
}

/***********************************************************************************************************************
 * @param buffer_frame - pointer pointing to a buffer storing the imported 24-bit bitmap image
 * @param width - width of the imported 24-bit bitmap image
 * @param height - height of the imported 24-bit bitmap image
 * @param _unused - this field is unused
 * @return
 **********************************************************************************************************************/
unsigned char *processMirrorY(unsigned char *buffer_frame, unsigned width, unsigned height, int _unused)
{
    return processMirrorYReference(buffer_frame, width, height, _unused);
}

/***********************************************************************************************************************
 * WARNING: Do not modify the implementation_driver and team info prototype (name, parameter, return value) !!!
 *          Do not forget to modify the team_name and team member information !!!
 **********************************************************************************************************************/
void print_team_info()
{
    // Please modify this field with something interesting
    char team_name[] = "ducklingogh";

    // Please fill in your information
    char student_first_name[] = "kyna";
    char student_last_name[] = "wu";
    char student_student_number[] = "1008214754";

    // Printing out team information
    printf("*******************************************************************************************************\n");
    printf("Team Information:\n");
    printf("\tteam_name: %s\n", team_name);
    printf("\tstudent_first_name: %s\n", student_first_name);
    printf("\tstudent_last_name: %s\n", student_last_name);
    printf("\tstudent_student_number: %s\n", student_student_number);
}

/***********************************************************************************************************************
 * My modifications below
 ***********************************************************************************************************************/

/*--------------------------------------------------------------------------------------
 * Operation definitions
 *------------------------------------------------------------------------------------*/

typedef enum
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    CW,
    CCW,
    MX,
    MY,
    UNKNOWN
} OpKind;

typedef struct
{
    OpKind kind;
    int val;
} Op;

/**
 * @brief Parse a string key into an OpKind.
 * @param k The input key string (e.g., "W", "CCW", "MX").
 * @return The corresponding OpKind enum, or UNKNOWN if not recognized.
 */
static inline OpKind parse_key(const char *k)
{
    size_t n = 0;
    while (k[n])
        ++n;

    if (n == 1)
    {
        switch (k[0])
        {
        case 'W':
            return UP;
        case 'A':
            return LEFT;
        case 'S':
            return DOWN;
        case 'D':
            return RIGHT;
        default:
            return UNKNOWN;
        }
    }
    else if (n == 2)
    {
        if (k[0] == 'C' && k[1] == 'W')
            return CW;
        if (k[0] == 'M' && k[1] == 'X')
            return MX;
        if (k[0] == 'M' && k[1] == 'Y')
            return MY;
        return UNKNOWN;
    }
    else if (n == 3)
    {
        if (k[0] == 'C' && k[1] == 'C' && k[2] == 'W')
            return CCW;
        return UNKNOWN;
    }

    return UNKNOWN;
}

/***********************************************************************************************************************
 * @brief Normalize an input key in-place: trims whitespace/CRLF and uppercases ASCII letters.
 **********************************************************************************************************************/
static inline void normalize_key(char *s)
{
    // trim leading
    size_t i = 0;
    while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n' || s[i] == '\r') ++i;
    if (i) memmove(s, s + i, strlen(s + i) + 1);

    // trim trailing
    size_t n = strlen(s);
    while (n && (s[n - 1] == ' ' || s[n - 1] == '\t' || s[n - 1] == '\n' || s[n - 1] == '\r')) s[--n] = '\0';

    // uppercase
    for (size_t j = 0; j < n; ++j) {
        if (s[j] >= 'a' && s[j] <= 'z') s[j] = (char)(s[j] - 'a' + 'A');
    }
}

/**
 * @brief Check if an operation is a movement (UP, DOWN, LEFT, RIGHT).
 */
static inline bool is_move(OpKind k) { return (k == UP || k == DOWN || k == LEFT || k == RIGHT); }

/**
 * @brief Check if an operation is a rotation (CW, CCW).
 */
static inline bool is_rot(OpKind k) { return (k == CW || k == CCW); }

/**
 * @brief Check if an operation is a mirror (MX, MY).
 */
static inline bool is_mirror(OpKind k) { return (k == MX || k == MY); }

/*--------------------------------------------------------------------------------------
 * Affine transforms (2x2 integer matrix + translation)
 *------------------------------------------------------------------------------------*/

typedef struct
{
    int a11, a12, a21, a22;
} Mat2;
typedef struct
{
    int x, y;
} Vec2;

/**
 * @brief Identity transformation matrix.
 */
static inline Mat2 matId(void) { return (Mat2){1, 0, 0, 1}; }

/**
 * @brief Clockwise 90° rotation matrix.
 */
static inline Mat2 matCW(void) { return (Mat2){0, -1, 1, 0}; }

/**
 * @brief Counterclockwise 90° rotation matrix.
 */
static inline Mat2 matCCW(void) { return (Mat2){0, 1, -1, 0}; }

/**
 * @brief Mirror over the X-axis matrix.
 */
static inline Mat2 matMX(void) { return (Mat2){1, 0, 0, -1}; }

/**
 * @brief Mirror over the Y-axis matrix.
 */
static inline Mat2 matMY(void) { return (Mat2){-1, 0, 0, 1}; }

/**
 * @brief Multiply two 2x2 matrices.
 * @param P Left matrix.
 * @param Q Right matrix.
 * @return Result of P * Q.
 */
static inline Mat2 mulM(Mat2 P, Mat2 Q)
{
    return (Mat2){
        P.a11 * Q.a11 + P.a12 * Q.a21, P.a11 * Q.a12 + P.a12 * Q.a22,
        P.a21 * Q.a11 + P.a22 * Q.a21, P.a21 * Q.a12 + P.a22 * Q.a22};
}

/**
 * @brief Multiply a matrix and a vector.
 * @param M Transformation matrix.
 * @param v Input vector.
 * @return Resulting transformed vector.
 */
static inline Vec2 mulMV(Mat2 M, Vec2 v)
{
    return (Vec2){M.a11 * v.x + M.a12 * v.y, M.a21 * v.x + M.a22 * v.y};
}

/*--------------------------------------------------------------------------------------
 * Sparse object representation (stores only non-white pixels)
 *------------------------------------------------------------------------------------*/

typedef struct
{
    int x, y;
    unsigned char r, g, b;
} Pix;

static Pix *g_pts = NULL;
static int g_npts = 0;
static bool g_init_sparse = false;

/**
 * @brief Initialize sparse pixel storage from a framebuffer.
 * @param fb Framebuffer pointer (RGB format).
 * @param w  Frame width.
 * @param h  Frame height.
 */
static void init_sparse_object(const unsigned char *fb, unsigned w, unsigned h)
{
    if (g_init_sparse)
        return;

    const int N = (int)w * (int)h;

    /* Count non-white pixels */
    int cnt = 0;
    for (int i = 0; i < N; i++)
    {
        const unsigned char *p = fb + i * 3;
        if (!(p[0] == 255 && p[1] == 255 && p[2] == 255))
            cnt++;
    }

    g_pts = (Pix *)malloc((size_t)cnt * sizeof(Pix));
    g_npts = cnt;

    /* Store non-white pixel data */
    int k = 0;
    for (int y = 0; y < (int)h; y++)
    {
        int row = y * (int)w * 3;
        for (int x = 0; x < (int)w; x++)
        {
            const unsigned char *p = fb + row + x * 3;
            if (!(p[0] == 255 && p[1] == 255 && p[2] == 255))
            {
                g_pts[k].x = x;
                g_pts[k].y = y;
                g_pts[k].r = p[0];
                g_pts[k].g = p[1];
                g_pts[k].b = p[2];
                k++;
            }
        }
    }

    g_init_sparse = true;
}

/*--------------------------------------------------------------------------------------
 * Cumulative transformation state
 *------------------------------------------------------------------------------------*/

static Mat2 g_A;
static Vec2 g_o;
static bool g_tf_init = false;

/**
 * @brief Reset global transformation to identity.
 */
static inline void reset_transform(void)
{
    g_A = matId();
    g_o = (Vec2){0, 0};
    g_tf_init = true;
}

/**
 * @brief Apply an operation to the global transformation (A, o).
 * @param w Frame width.
 * @param h Frame height.
 * @param op Operation to apply.
 */
static inline void apply_op_to_transform(unsigned w, unsigned h, Op op)
{
    if (!g_tf_init)
        reset_transform();

    switch (op.kind)
    {
    case UP:
        g_o.y -= op.val;
        break;
    case DOWN:
        g_o.y += op.val;
        break;
    case LEFT:
        g_o.x -= op.val;
        break;
    case RIGHT:
        g_o.x += op.val;
        break;

    case CW:
    {
        int r = ((op.val % 4) + 4) % 4;
        while (r--)
        {
            Mat2 R = matCW();
            Vec2 t = (Vec2){(int)h - 1, 0};
            g_o = mulMV(R, g_o);
            g_o.x += t.x;
            g_o.y += t.y;
            g_A = mulM(R, g_A);
        }
    }
    break;

    case CCW:
    {
        int r = ((op.val % 4) + 4) % 4;
        while (r--)
        {
            Mat2 R = matCCW();
            Vec2 t = (Vec2){0, (int)w - 1};
            g_o = mulMV(R, g_o);
            g_o.x += t.x;
            g_o.y += t.y;
            g_A = mulM(R, g_A);
        }
    }
    break;

    case MX:
    {
        Mat2 F = matMX();
        Vec2 t = (Vec2){0, (int)h - 1};
        g_o = mulMV(F, g_o);
        g_o.x += t.x;
        g_o.y += t.y;
        g_A = mulM(F, g_A);
    }
    break;

    case MY:
    {
        Mat2 F = matMY();
        Vec2 t = (Vec2){(int)w - 1, 0};
        g_o = mulMV(F, g_o);
        g_o.x += t.x;
        g_o.y += t.y;
        g_A = mulM(F, g_A);
    }
    break;

    default:
        break;
    }
}

/*--------------------------------------------------------------------------------------
 * Sparse rendering
 *------------------------------------------------------------------------------------*/

/**
 * @brief Render sparse object onto framebuffer using current transform.
 * @param fb Framebuffer pointer.
 * @param w  Frame width.
 * @param h  Frame height.
 */
static inline void render_sparse_object(unsigned char *fb, unsigned w, unsigned h)
{
    memset(fb, 255, (size_t)w * (size_t)h * 3u);

    for (int i = 0; i < g_npts; i++)
    {
        int x = g_pts[i].x, y = g_pts[i].y;
        Vec2 q = mulMV(g_A, (Vec2){x, y});
        q.x += g_o.x;
        q.y += g_o.y;

        if ((unsigned)q.x < w && (unsigned)q.y < h)
        {
            /* use size_t for safe byte addressing on large images */
            size_t dp = ((size_t)q.y * (size_t)w + (size_t)q.x) * 3u;
            fb[dp]     = g_pts[i].r;
            fb[dp + 1] = g_pts[i].g;
            fb[dp + 2] = g_pts[i].b;
        }
    }
}

/*--------------------------------------------------------------------------------------
 * Window compression and reference replay
 *------------------------------------------------------------------------------------*/

/**
 * @brief Compress a window of operations by merging redundant or canceling ones.
 * @param sv   Source key-value sequence.
 * @param base Base index in window.
 * @param win  Window size.
 * @param out  Output array for compressed operations.
 * @param m_out Pointer to resulting count.
 */
static inline void compress_window(const struct kv *sv, int base, int win, Op out[], int *m_out)
{
    Op comp[25];
    int m = 0;

    for (int j = 0; j < win; j++)
    {
        Op cur = (Op){parse_key(sv[base + j].key), sv[base + j].value};

        if (m > 0)
        {
            Op *prev = &comp[m - 1];

            /* Merge adjacent identical moves */
            if (is_move(prev->kind) && prev->kind == cur.kind && is_move(cur.kind))
            {
                prev->val += cur.val;
                if (prev->val == 0)
                    m--;
                continue;
            }

            /* Fold consecutive rotations */
            if (is_rot(prev->kind) && is_rot(cur.kind))
            {
                int net = (prev->kind == CW ? +prev->val : -prev->val) + (cur.kind == CW ? +cur.val : -cur.val);
                net %= 4;
                if (net < 0)
                    net += 4;
                if (net == 0)
                {
                    m--;
                }
                else
                {
                    prev->kind = CW;
                    prev->val = (net == 1) ? 1 : (net == 2) ? 2
                                                            : 3;
                }
                continue;
            }

            /* Cancel adjacent identical mirrors */
            if (is_mirror(prev->kind) && cur.kind == prev->kind)
            {
                m--;
                continue;
            }
        }

        comp[m++] = cur;
    }

    for (int i = 0; i < m; i++)
        out[i] = comp[i];
    *m_out = m;
}

/**
 * @brief Apply one operation to a framebuffer using reference functions.
 * @param fb  Framebuffer pointer.
 * @param w   Frame width.
 * @param h   Frame height.
 * @param op  Operation to apply.
 * @return Updated framebuffer pointer.
 */
static inline unsigned char *apply_one_ref(unsigned char *fb, unsigned w, unsigned h, Op op)
{
    switch (op.kind)
    {
    case UP:
        return processMoveUpReference(fb, w, h, op.val);
    case DOWN:
        return processMoveDownReference(fb, w, h, op.val);
    case LEFT:
        return processMoveLeftReference(fb, w, h, op.val);
    case RIGHT:
        return processMoveRightReference(fb, w, h, op.val);
    case CW:
        return processRotateCWReference(fb, w, h, op.val);
    case CCW:
        return processRotateCCWReference(fb, w, h, op.val);
    case MX:
        return processMirrorXReference(fb, w, h, op.val);
    case MY:
        return processMirrorYReference(fb, w, h, op.val);
    default:
        return fb;
    }
}

/***********************************************************************************************************************
 * WARNING: Do not modify the implementation_driver and team info prototype (name, parameter, return value) !!!
 *          You can modify anything else in this file
 ***********************************************************************************************************************
 * @param sensor_values - structure stores parsed key value pairs of program instructions
 * @param sensor_values_count - number of valid sensor values parsed from sensor log file or commandline console
 * @param frame_buffer - pointer pointing to a buffer storing the imported  24-bit bitmap image
 * @param width - width of the imported 24-bit bitmap image
 * @param height - height of the imported 24-bit bitmap image
 * @param grading_mode - turns off verification and turn on instrumentation
 ***********************************************************************************************************************
 *
 **********************************************************************************************************************/
void implementation_driver(struct kv *sensor_values, int sensor_values_count, unsigned char *frame_buffer,
                           unsigned int width, unsigned int height, bool grading_mode)
{

    /* One-time sparse object build from the initial frame */
    init_sparse_object(frame_buffer, width, height);
    reset_transform();
    int processed = 0;
    for (int i = 0; i < sensor_values_count; i++)
    {
        /* normalize the key to avoid UNKNOWN due to whitespace/CRLF/case */
        if (sensor_values[i].key) {
            normalize_key(sensor_values[i].key);
        }

        Op op = (Op){parse_key(sensor_values[i].key), sensor_values[i].value};
        if (op.kind != UNKNOWN)
            apply_op_to_transform(width, height, op);
        if (++processed % 25 == 0)
        {
            render_sparse_object(frame_buffer, width, height);
            if (grading_mode)
            {
                recordFrame(frame_buffer, width, height, grading_mode);
            }
            else
            {
                verifyFrame(frame_buffer, width, height, grading_mode);
            }
        }
    }
    return;
}
