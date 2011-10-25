#ifndef PANORAMAINTERNAL_H
#define PANORAMAINTERNAL_H

/** Adds a pointer to the private implementation class for this class */
#define PANORAMA_DECLARE_PRIVATE(Class) \
private: \
    inline Class##Private *priv_func() { return reinterpret_cast<Class##Private *>(priv_ptr); } \
    inline const Class##Private *priv_func() const { return reinterpret_cast<const Class##Private *>(priv_ptr); } \
    friend class Class##Private; \
    void *priv_ptr;

/** Adds a pointer to the public class associated with this private class */
#define PANORAMA_DECLARE_PUBLIC(Class) \
public: \
    inline Class *pub_func() { return static_cast<Class *>(pub_ptr); } \
    inline const Class *pub_func() const { return static_cast<const Class *>(pub_ptr); } \
private: \
    friend class Class; \
    void *pub_ptr;

/** Retrieves a pointer called "priv" pointing to the private implementation class */
#define PANORAMA_PRIVATE(Class) Class##Private *const priv = priv_func()

/** Retrieves a pointer called "pub" pointing to the public class associated with this private class */
#define PANORAMA_PUBLIC(Class) Class *const pub = pub_func()

/** Constructs the private implementation class for this class */
#define PANORAMA_INITIALIZE(Class) priv_ptr = new Class##Private(); PANORAMA_PRIVATE(Class); priv->pub_ptr = this

/** Destroys the private implementation class for this class */
#define PANORAMA_UNINITIALIZE(Class) PANORAMA_PRIVATE(Class); delete priv

#endif // PANORAMAINTERNAL_H
