//
//  geo_uri.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/18/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#ifndef geo_uri_hpp
#define geo_uri_hpp

#include <stdio.h>
#include <string>
#include <map>
#include "character_bitset.hpp"

class GeoUri {
//    /**
//     * The coordinate reference system used by GPS (the default).
//     */
//    public static final String CRS_WGS84 = "wgs84";
//    
//    /**
//     * The characters which are allowed to exist un-encoded inside of a
//     * parameter value.
//     */
//    private static final boolean validParameterValueCharacters[] = new boolean[128];
//    static {
//        for (int i = '0'; i <= '9'; i++) {
//            validParameterValueCharacters[i] = true;
//        }
//        for (int i = 'A'; i <= 'Z'; i++) {
//            validParameterValueCharacters[i] = true;
//        }
//        for (int i = 'a'; i <= 'z'; i++) {
//            validParameterValueCharacters[i] = true;
//        }
//        String s = "!$&'()*+-.:[]_~";
//        for (int i = 0; i < s.length(); i++) {
//            char c = s.charAt(i);
//            validParameterValueCharacters[c] = true;
//        }
//    }
//    
//    /**
//     * Finds hex values in a parameter value.
//     */
//    private static final Pattern hexPattern = Pattern.compile("(?i)%([0-9a-f]{2})");
//    
//    private static final String PARAM_CRS = "crs";
//    private static final String PARAM_UNCERTAINTY = "u";
//    
//    private final Double coordA;
//    private final Double coordB;
//    private final Double coordC;
//    private final String crs;
//    private final Double uncertainty;
//    private final Map<String, String> parameters;
//    
//    private GeoUri(Builder builder) {
//        this.coordA = (builder.coordA == null) ? Double.valueOf(0.0) : builder.coordA;
//        this.coordB = (builder.coordB == null) ? Double.valueOf(0.0) : builder.coordB;
//        this.coordC = builder.coordC;
//        this.crs = builder.crs;
//        this.uncertainty = builder.uncertainty;
//        this.parameters = Collections.unmodifiableMap(builder.parameters);
//    }

public:
    typedef std::shared_ptr<GeoUri> Ptr;
    
    static GeoUri::Ptr parse(const std::string& uri);
    
//    private static void handleEndOfCoordinate(ClearableStringBuilder buffer, Builder builder) {
//        String s = buffer.getAndClear();
//        
//        if (builder.coordA == null) {
//            try {
//                builder.coordA = Double.parseDouble(s);
//            } catch (NumberFormatException e) {
//                throw new IllegalArgumentException(Messages.INSTANCE.getExceptionMessage(22, "A"), e);
//            }
//            return;
//        }
//        
//        if (builder.coordB == null) {
//            try {
//                builder.coordB = Double.parseDouble(s);
//            } catch (NumberFormatException e) {
//                throw new IllegalArgumentException(Messages.INSTANCE.getExceptionMessage(22, "B"), e);
//            }
//            return;
//        }
//        
//        if (builder.coordC == null) {
//            try {
//                builder.coordC = Double.parseDouble(s);
//            } catch (NumberFormatException e) {
//                throw new IllegalArgumentException(Messages.INSTANCE.getExceptionMessage(22, "C"), e);
//            }
//            return;
//        }
//    }
//    
//    private static void addParameter(String name, String value, Builder builder) {
//        value = decodeParameterValue(value);
//        
//        if (PARAM_CRS.equalsIgnoreCase(name)) {
//            builder.crs = value;
//            return;
//        }
//        
//        if (PARAM_UNCERTAINTY.equalsIgnoreCase(name)) {
//            try {
//                builder.uncertainty = Double.valueOf(value);
//                return;
//            } catch (NumberFormatException e) {
//                //if it can't be parsed, then treat it as an ordinary parameter
//            }
//        }
//        
//        builder.parameters.put(name, value);
//    }
//    
//    private static void handleEndOfParameter(ClearableStringBuilder buffer, String paramName, Builder builder) {
//        String s = buffer.getAndClear();
//        
//        if (paramName == null) {
//            if (s.length() > 0) {
//                addParameter(s, "", builder);
//            }
//            return;
//        }
//        
//        addParameter(paramName, s, builder);
//    }
//    
//    /**
//     * Gets the first coordinate (latitude).
//     * @return the first coordinate or null if there is none
//     */
//    public Double getCoordA() {
//        return coordA;
//    }
//    
//    /**
//     * Gets the second coordinate (longitude).
//     * @return the second coordinate or null if there is none
//     */
//    public Double getCoordB() {
//        return coordB;
//    }
//    
//    /**
//     * Gets the third coordinate (altitude).
//     * @return the third coordinate or null if there is none
//     */
//    public Double getCoordC() {
//        return coordC;
//    }
//    
//    /**
//     * Gets the coordinate reference system.
//     * @return the coordinate reference system or null if using the default
//     * (WGS-84)
//     */
//    public String getCrs() {
//        return crs;
//    }
//    
//    /**
//     * Gets the uncertainty (how accurate the coordinates are).
//     * @return the uncertainty (in meters) or null if not set
//     */
//    public Double getUncertainty() {
//        return uncertainty;
//    }
//    
//    /**
//     * Gets a parameter value.
//     * @param name the parameter name
//     * @return the parameter value or null if not found
//     */
//    public String getParameter(String name) {
//        return parameters.get(name);
//    }
//    
//    /**
//     * Gets all the parameters.
//     * @return all the parameters
//     */
//    public Map<String, String> getParameters() {
//        return parameters;
//    }
//    
//    /**
//     * Creates a {@link URI} object from this geo URI.
//     * @return the {@link URI} object
//     */
//    public URI toUri() {
//        return URI.create(toString());
//    }
//    
//    /**
//     * Converts this geo URI to its string representation.
//     * @return the geo URI's string representation
//     */
//    @Override
//    public String toString() {
//        return toString(6);
//    }
//    
//    /**
//     * Converts this geo URI to its string representation.
//     * @param decimals the number of decimals to display for floating point
//     * values
//     * @return the geo URI's string representation
//     */
//    public String toString(int decimals) {
//        VCardFloatFormatter formatter = new VCardFloatFormatter(decimals);
//        StringBuilder sb = new StringBuilder("geo:");
//        
//        sb.append(formatter.format(coordA));
//        sb.append(',');
//        sb.append(formatter.format(coordB));
//        
//        if (coordC != null) {
//            sb.append(',');
//            sb.append(coordC);
//        }
//        
//        //if the CRS is WGS-84, then it doesn't have to be displayed
//        if (crs != null && !crs.equalsIgnoreCase(CRS_WGS84)) {
//            writeParameter(PARAM_CRS, crs, sb);
//        }
//        
//        if (uncertainty != null) {
//            writeParameter(PARAM_UNCERTAINTY, formatter.format(uncertainty), sb);
//        }
//        
//        for (Map.Entry<String, String> entry : parameters.entrySet()) {
//            String name = entry.getKey();
//            String value = entry.getValue();
//            writeParameter(name, value, sb);
//        }
//        
//        return sb.toString();
//    }
//    
//    /**
//     * Writes a parameter to a string.
//     * @param name the parameter name
//     * @param value the parameter value
//     * @param sb the string to write to
//     */
//    private void writeParameter(String name, String value, StringBuilder sb) {
//        sb.append(';').append(name).append('=').append(encodeParameterValue(value));
//    }
//    
//    /**
//     * Encodes a string for safe inclusion in a parameter value.
//     * @param value the string to encode
//     * @return the encoded value
//     */
//    private static String encodeParameterValue(String value) {
//        StringBuilder sb = null;
//        for (int i = 0; i < value.length(); i++) {
//            char c = value.charAt(i);
//            if (c < validParameterValueCharacters.length && validParameterValueCharacters[c]) {
//                if (sb != null) {
//                    sb.append(c);
//                }
//            } else {
//                if (sb == null) {
//                    sb = new StringBuilder(value.length() * 2);
//                    sb.append(value.substring(0, i));
//                }
//                String hex = Integer.toString(c, 16);
//                sb.append('%').append(hex);
//            }
//        }
//        return (sb == null) ? value : sb.toString();
//    }
//    
//    /**
//     * Decodes escaped characters in a parameter value.
//     * @param value the parameter value
//     * @return the decoded value
//     */
//    private static String decodeParameterValue(String value) {
//        Matcher m = hexPattern.matcher(value);
//        StringBuffer sb = null;
//        
//        while (m.find()) {
//            if (sb == null) {
//                sb = new StringBuffer(value.length());
//            }
//            
//            int hex = Integer.parseInt(m.group(1), 16);
//            m.appendReplacement(sb, Character.toString((char) hex));
//        }
//        
//        if (sb == null) {
//            return value;
//        }
//        
//        m.appendTail(sb);
//        return sb.toString();
//    }
//    
//    @Override
//    public int hashCode() {
//        final int prime = 31;
//        int result = 1;
//        result = prime * result + ((coordA == null) ? 0 : coordA.hashCode());
//        result = prime * result + ((coordB == null) ? 0 : coordB.hashCode());
//        result = prime * result + ((coordC == null) ? 0 : coordC.hashCode());
//        result = prime * result + ((crs == null) ? 0 : crs.toLowerCase().hashCode());
//        result = prime * result + ((parameters == null) ? 0 : StringUtils.toLowerCase(parameters).hashCode());
//        result = prime * result + ((uncertainty == null) ? 0 : uncertainty.hashCode());
//        return result;
//    }
//    
//    @Override
//    public boolean equals(Object obj) {
//        if (this == obj) return true;
//        if (obj == null) return false;
//        if (getClass() != obj.getClass()) return false;
//        GeoUri other = (GeoUri) obj;
//        if (coordA == null) {
//            if (other.coordA != null) return false;
//        } else if (!coordA.equals(other.coordA)) return false;
//        if (coordB == null) {
//            if (other.coordB != null) return false;
//        } else if (!coordB.equals(other.coordB)) return false;
//        if (coordC == null) {
//            if (other.coordC != null) return false;
//        } else if (!coordC.equals(other.coordC)) return false;
//        if (crs == null) {
//            if (other.crs != null) return false;
//        } else if (!crs.equalsIgnoreCase(other.crs)) return false;
//        if (uncertainty == null) {
//            if (other.uncertainty != null) return false;
//        } else if (!uncertainty.equals(other.uncertainty)) return false;
//        if (parameters == null) {
//            if (other.parameters != null) return false;
//        } else {
//            if (other.parameters == null) return false;
//            if (parameters.size() != other.parameters.size()) return false;
//            
//            Map<String, String> parametersLower = StringUtils.toLowerCase(parameters);
//            Map<String, String> otherParametersLower = StringUtils.toLowerCase(other.parameters);
//            if (!parametersLower.equals(otherParametersLower)) return false;
//        }
//        return true;
//    }
//    

};


/**
 * Builder class for {@link GeoUri}.
 * @author Michael Angstadt
 */
class GeoUriBuilder {
private:
    double _coordA;
    double _coordB;
    double _coordC;
    std::string _crs;
    double _uncertainty;
    std::map<std::string, std::string> _parameters;
    CharacterBitSet::Ptr _validParamChars; // = new CharacterBitSet("a-zA-Z0-9-")
    
public:
    typedef std::shared_ptr<GeoUriBuilder> Ptr;
    
    double coordB();
    
    GeoUriBuilder(double coordA, double coordB);
    GeoUriBuilder(const GeoUri::Ptr& original);
    void CoordA(double coordA);
    void CoordB(double coordB);
    void CoordC(double coordC);
    void Crs(const std::string& crs);
    void Uncertainty(double uncertainty);
    void Parameter(const std::string& name, const std::string& value);
    GeoUri::Ptr build();
};


#endif /* geo_uri_hpp */
