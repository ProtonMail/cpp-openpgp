//
//  date_or_time_property.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/10/17.
//
//  The MIT License
// 
//  Copyright (c) 2019 Proton Technologies AG
// 
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
// 
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
// 
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.

#include "date_or_time_property.hpp"


//
//
//
//private String text;
//private Date date;
//private PartialDate partialDate;
//private boolean dateHasTime;
//
///**
// * Creates a date-and-or-time property.
// * @param date the date value
// */
//public DateOrTimeProperty(Date date) {
//    this(date, false);
//}
//
///**
// * Creates a date-and-or-time property.
// * @param date the date value
// * @param hasTime true to include the date's time component, false if it's
// * strictly a date
// */
//public DateOrTimeProperty(Date date, boolean hasTime) {
//    setDate(date, hasTime);
//}
//
///**
// * Creates a date-and-or-time property.
// * @param partialDate the partial date value (vCard 4.0 only)
// */
//public DateOrTimeProperty(PartialDate partialDate) {
//    setPartialDate(partialDate);
//}
//
///**
// * Creates a date-and-or-time property.
// * @param text the text value (vCard 4.0 only)
// */
//public DateOrTimeProperty(String text) {
//    setText(text);
//}
//
///**
// * Copy constructor.
// * @param original the property to make a copy of
// */
//public DateOrTimeProperty(DateOrTimeProperty original) {
//    super(original);
//    text = original.text;
//    date = (original.date == null) ? null : new Date(original.date.getTime());
//    partialDate = original.partialDate;
//    dateHasTime = original.dateHasTime;
//}
//
///**
// * Gets the date value.
// * @return the date value or null if not set
// */
//public Date getDate() {
//    return date;
//}
//
///**
// * Sets the value of this property to a complete date.
// * @param date the date
// * @param hasTime true to include the date's time component, false if it's
// * strictly a date
// */
//public void setDate(Date date, boolean hasTime) {
//    this.date = date;
//    this.dateHasTime = (date == null) ? false : hasTime;
//    text = null;
//    partialDate = null;
//}
//
///**
// * Gets the reduced accuracy or truncated date. This is only supported by
// * vCard 4.0.
// * @return the reduced accuracy or truncated date or null if not set
// * @see <a href="http://tools.ietf.org/html/rfc6350">RFC 6350 p.12-14</a>
// */
//public PartialDate getPartialDate() {
//    return partialDate;
//}
//
///**
// * <p>
// * Sets the value of this property to a reduced accuracy or truncated date.
// * This is only supported by vCard 4.0.
// * </p>
// *
// * <pre class="brush:java">
// * Birthday bday = new Birthday();
// * bday.setPartialDate(PartialDate.date(null, 4, 20)); //April 20
// * </pre>
// * @param partialDate the reduced accuracy or truncated date
// * @see <a href="http://tools.ietf.org/html/rfc6350">RFC 6350 p.12-14</a>
// */
//public void setPartialDate(PartialDate partialDate) {
//    this.partialDate = partialDate;
//    dateHasTime = (partialDate == null) ? false : partialDate.hasTimeComponent();
//    text = null;
//    date = null;
//}
//
///**
// * Gets the text value of this type. This is only supported by vCard 4.0.
// * @return the text value or null if not set
// */
//public String getText() {
//    return text;
//}
//
///**
// * Sets the value of this property to a text string. This is only supported
// * by vCard 4.0.
// * @param text the text value
// */
//public void setText(String text) {
//    this.text = text;
//    date = null;
//    partialDate = null;
//    dateHasTime = false;
//}
//
///**
// * Determines whether the "date" or "partialDate" fields have a time
// * component.
// * @return true if the date has a time component, false if it's strictly a
// * date, and false if a text value is defined
// */
//public boolean hasTime() {
//    return dateHasTime;
//}
//
///**
// * <p>
// * Gets the type of calendar that is used for a date or date-time property
// * value.
// * </p>
// * <p>
// * <b>Supported versions:</b> {@code 4.0}
// * </p>
// * @return the type of calendar or null if not found
// * @see VCardParameters#getCalscale
// */
//public Calscale getCalscale() {
//    return parameters.getCalscale();
//}
//
///**
// * <p>
// * Sets the type of calendar that is used for a date or date-time property
// * value.
// * </p>
// * <p>
// * <b>Supported versions:</b> {@code 4.0}
// * </p>
// * @param calscale the type of calendar or null to remove
// * @see VCardParameters#setCalscale
// */
//public void setCalscale(Calscale calscale) {
//    parameters.setCalscale(calscale);
//}
//
//@Override
//public String getLanguage() {
//    return super.getLanguage();
//}
//
//@Override
//public void setLanguage(String language) {
//    super.setLanguage(language);
//}
//
////@Override
//public String getAltId() {
//    return parameters.getAltId();
//}
//
////@Override
//public void setAltId(String altId) {
//    parameters.setAltId(altId);
//}
//
//@Override
//protected void _validate(List<ValidationWarning> warnings, VCardVersion version, VCard vcard) {
//    if (date == null && partialDate == null && text == null) {
//        warnings.add(new ValidationWarning(8));
//    }
//    
//    if (version == VCardVersion.V2_1 || version == VCardVersion.V3_0) {
//        if (text != null) {
//            warnings.add(new ValidationWarning(11));
//        }
//        if (partialDate != null) {
//            warnings.add(new ValidationWarning(12));
//        }
//    }
//}
//
//@Override
//protected Map<String, Object> toStringValues() {
//    Map<String, Object> values = new LinkedHashMap<String, Object>();
//    values.put("text", text);
//    values.put("date", date);
//    values.put("dateHasTime", dateHasTime);
//    values.put("partialDate", partialDate);
//    return values;
//}
//
//@Override
//public int hashCode() {
//    final int prime = 31;
//    int result = super.hashCode();
//    result = prime * result + ((date == null) ? 0 : date.hashCode());
//    result = prime * result + (dateHasTime ? 1231 : 1237);
//    result = prime * result + ((partialDate == null) ? 0 : partialDate.hashCode());
//    result = prime * result + ((text == null) ? 0 : text.hashCode());
//    return result;
//}
//
//@Override
//public boolean equals(Object obj) {
//    if (this == obj) return true;
//    if (!super.equals(obj)) return false;
//    DateOrTimeProperty other = (DateOrTimeProperty) obj;
//    if (date == null) {
//        if (other.date != null) return false;
//    } else if (!date.equals(other.date)) return false;
//    if (dateHasTime != other.dateHasTime) return false;
//    if (partialDate == null) {
//        if (other.partialDate != null) return false;
//    } else if (!partialDate.equals(other.partialDate)) return false;
//    if (text == null) {
//        if (other.text != null) return false;
//    } else if (!text.equals(other.text)) return false;
//    return true;
//}
