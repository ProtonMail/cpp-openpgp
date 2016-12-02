//
//  binary_property.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/10/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#include "binary_property.hpp"
//
//
//
///**
// * Represents a property whose value contains binary data.
// * @author Michael Angstadt
// * @param <T> the class used for representing the content type of the resource
// */
//public abstract class BinaryProperty<T extends MediaTypeParameter> extends VCardProperty implements HasAltId {
//    /**
//     * The decoded data.
//     */
//    protected byte[] data;
//    
//    /**
//     * The URL to the resource.
//     */
//    protected String url;
//    
//    /**
//     * The content type of the resource (for example, a JPEG image).
//     */
//    protected T contentType;
//    
//    public BinaryProperty() {
//        //empty
//    }
//    
//    /**
//     * Creates a binary property.
//     * @param url the URL to the resource
//     * @param type the content type
//     */
//    public BinaryProperty(String url, T type) {
//        setUrl(url, type);
//    }
//    
//    /**
//     * Creates a binary property.
//     * @param data the binary data
//     * @param type the content type
//     */
//    public BinaryProperty(byte[] data, T type) {
//        setData(data, type);
//    }
//    
//    /**
//     * Creates a binary property.
//     * @param in an input stream to the binary data (will be closed)
//     * @param type the content type
//     * @throws IOException if there is a problem reading from the input stream
//     */
//    public BinaryProperty(InputStream in, T type) throws IOException {
//        this(new Gobble(in).asByteArray(), type);
//    }
//    
//    /**
//     * Creates a binary property.
//     * @param file the file containing the binary data
//     * @param type the content type
//     * @throws IOException if there is a problem reading from the file
//     */
//    public BinaryProperty(File file, T type) throws IOException {
//        this(new BufferedInputStream(new FileInputStream(file)), type);
//    }
//    
//    /**
//     * Copy constructor.
//     * @param original the property to make a copy of
//     */
//    public BinaryProperty(BinaryProperty<T> original) {
//        super(original);
//        data = (original.data == null) ? null : original.data.clone();
//        url = original.url;
//        contentType = original.contentType;
//    }
//    
//    /**
//     * Gets the binary data of the resource.
//     * @return the binary data or null if there is none
//     */
//    public byte[] getData() {
//        return data;
//    }
//    
//    /**
//     * Sets the binary data of the resource.
//     * @param data the binary data
//     * @param type the content type (e.g. "JPEG image")
//     */
//    public void setData(byte[] data, T type) {
//        this.url = null;
//        this.data = data;
//        setContentType(type);
//    }
//    
//    /**
//     * Gets the URL to the resource
//     * @return the URL or null if there is none
//     */
//    public String getUrl() {
//        return url;
//    }
//    
//    /**
//     * Sets the URL to the resource.
//     * @param url the URL
//     * @param type the content type (e.g. "JPEG image")
//     */
//    public void setUrl(String url, T type) {
//        this.url = url;
//        this.data = null;
//        setContentType(type);
//    }
//    
//    /**
//     * Gets the content type of the resource.
//     * @return the content type (e.g. "JPEG image")
//     */
//    public T getContentType() {
//        return contentType;
//    }
//    
//    /**
//     * Sets the content type of the resource.
//     * @param contentType the content type (e.g. "JPEG image")
//     */
//    public void setContentType(T contentType) {
//        this.contentType = contentType;
//    }
//    
//    /**
//     * Gets the vCard 4.0 TYPE parameter. This should NOT be used to get the
//     * TYPE parameter for 2.1/3.0 vCards. Use {@link #getContentType} instead.
//     * <p>
//     * <b>Supported versions:</b> {@code 4.0}
//     * </p>
//     * @return the TYPE value (typically, this will be either "work" or "home")
//     * or null if it doesn't exist
//     */
//    public String getType() {
//        return parameters.getType();
//    }
//    
//    /**
//     * Sets the vCard 4.0 TYPE parameter. This should NOT be used to set the
//     * TYPE parameter for 2.1/3.0 vCards. Use {@link #setContentType} instead.
//     * <p>
//     * <b>Supported versions:</b> {@code 4.0}
//     * </p>
//     * @param type the TYPE value (should be either "work" or "home") or null to
//     * remove
//     */
//    public void setType(String type) {
//        parameters.setType(type);
//    }
//    
//    @Override
//    public List<Pid> getPids() {
//        return super.getPids();
//    }
//    
//    @Override
//    public Integer getPref() {
//        return super.getPref();
//    }
//    
//    @Override
//    public void setPref(Integer pref) {
//        super.setPref(pref);
//    }
//    
//    //@Override
//    public String getAltId() {
//        return parameters.getAltId();
//    }
//    
//    //@Override
//    public void setAltId(String altId) {
//        parameters.setAltId(altId);
//    }
//    
//    @Override
//    protected void _validate(List<ValidationWarning> warnings, VCardVersion version, VCard vcard) {
//        if (url == null && data == null) {
//            warnings.add(new ValidationWarning(8));
//        }
//    }
//    
//    @Override
//    protected Map<String, Object> toStringValues() {
//        Map<String, Object> values = new LinkedHashMap<String, Object>();
//        values.put("data", (data == null) ? "null" : "length: " + data.length);
//        values.put("url", url);
//        values.put("contentType", contentType);
//        return values;
//    }
//    
//    @Override
//    public int hashCode() {
//        final int prime = 31;
//        int result = super.hashCode();
//        result = prime * result + ((contentType == null) ? 0 : contentType.hashCode());
//        result = prime * result + Arrays.hashCode(data);
//        result = prime * result + ((url == null) ? 0 : url.hashCode());
//        return result;
//    }
//    
//    @Override
//    public boolean equals(Object obj) {
//        if (this == obj) return true;
//        if (!super.equals(obj)) return false;
//        BinaryProperty<?> other = (BinaryProperty<?>) obj;
//        if (contentType == null) {
//            if (other.contentType != null) return false;
//        } else if (!contentType.equals(other.contentType)) return false;
//        if (!Arrays.equals(data, other.data)) return false;
//        if (url == null) {
//            if (other.url != null) return false;
//        } else if (!url.equals(other.url)) return false;
//        return true;
//    }
//}
