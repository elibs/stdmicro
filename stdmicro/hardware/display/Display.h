#ifndef __DISPLAY_H
#define __DISPLAY_H

class Display
{
public:

    /**
     * Draw a buffer to the display. It is expected that the buffer contains an
     * entire screen buffer of pixel information.
     *
     * @param data The pixel data for the display to draw.
     * @param size The size of the data array.
     */
    virtual void draw(const unsigned char* data, size_t size) = 0;

    virtual constexpr unsigned int dpi(void) const = 0;
    virtual constexpr unsigned int height(void) const = 0;
    virtual constexpr unsigned int width(void) const = 0;

    /**
     * Redraw a part of the screen, not the entire thing
     *
     * @param data The image data (with appropriate bit depth).
     * @param size The number of bytes in the data.
     * @param x The starting horizontal pixel bank. NOTE: This goes in 8-pixel
     *     chunks.
     * @param y The starting vertical pizel bank. NOTE: This goes in 1-pixel
     *     chunks.
     * @param width The width of your image. NOTE: This value must be a
     *     multiple of 8, and will be converted internally to an end-bank value
     *     (must be at least x).
     * @param height The height of your image. NOTE: This gets converted to
     *     ending y-bank internally.
     */
    virtual int drawPartial(const unsigned char* data, size_t size, size_t x, size_t y, size_t width, size_t height) = 0;

    /**
     * Clear the screen, once this function returns, the display should be
     * showing its default pixel array (typically black, or white).
     */
    virtual void clear(void) = 0;

    /**
     * Power the display on.
     */
    virtual void powerOn(void) = 0;

    /**
     * Power the display off.
     */
    virtual void powerOff(void) = 0;

    /**
     * Restart the display (this is useful for displays which support a sleep
     * mode, and can be powered off without needing a full re-instantiation on
     * a restart).
     */
    virtual void restart(void) = 0;

    /**
     * Initialize the display. This is _not_ the constructor as it is possible
     * tha the display is being constructed prior to it being ready for use.
     */
    virtual void init(void) = 0;
};

#endif
