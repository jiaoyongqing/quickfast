// Copyright (c) 2009, Object Computing, Inc.
// All rights reserved.
// See the file license.txt for licensing information.
#ifdef _MSC_VER
# pragma once
#endif
#ifndef SEGMENTBODY_H
#define SEGMENTBODY_H
#include "SegmentBody_fwd.h"
#include "FieldInstruction_fwd.h"
#include "SchemaElement.h"
#include <Common/QuickFAST_Export.h>

namespace QuickFAST{
  namespace Codecs{
    /// @brief A decorated collection of FieldInstructions.
    ///
    /// The template representation of the set of fields instructions that
    /// make up a Message, a Group, or a Segment
    class QuickFAST_Export SegmentBody
      : public SchemaElement
    {
    public:
      /// @brief Construct an empty segment body.
      SegmentBody(size_t pmapBits = 0);

      /// @brief Destructor.
      virtual ~SegmentBody()
      {
      }

      /// @brief Implement the dictionary= attribute.
      ///
      /// Defines an dictionary to be used for this element.
      /// Not applicable to all field instructions so the default implementation
      /// throws a TemplateDefinition error.
      /// @param name is the dictionary= attribute of the segment-defining element
      virtual void setDictionaryName(const std::string & name);

      virtual void setApplicationType(const std::string & type, const std::string & ns);
      virtual void addLengthInstruction(FieldInstructionPtr & field);
      virtual void addInstruction(FieldInstructionPtr & field);

      virtual void finalize();

      /// @brief Retrieve the typeref information
      /// @returns the typeref for this segment.
      const std::string & getApplicationType()const
      {
        return applicationType_;
      }

      /// @brief Enable the addLengthInstruction() method.
      void allowLengthField()
      {
        allowLengthField_ = true;
      }

      /// @brief How many field instructions are defined by this segment?
      ///
      /// The number of field instructions != the number of fields that will
      /// be Xcoded because groups and template references may be merged into
      /// the Xcoded field set.  For the number of fields, @see fieldCount()
      /// @returns the FieldInstruction count.
      size_t size()const
      {
        return instructions_.size();
      }

      /// @brief How many fields will be Xcoded by this segment?
      ///
      /// The number of field instructions != the number of fields that will
      /// be Xcoded because groups and template references may be merged into
      /// the Xcoded field set.  For the number of field instructions, @see size()
      /// @returns the maximum number of fields this segment might Xcode.
      size_t fieldCount() const;

      /// @brief How many bits are needed in the presence map.
      /// @returns the maximum number of presence bits that might be used.
      size_t presenceMapBitCount()const
      {
        return presenceMapBits_;
      }

      /// @brief Look up a field index by name.
      /// @param name is the name of the desired field.
      /// @returns the index to this field, or >=instructionCount if not found.
      size_t instructionIndex(const std::string & name)const;

      /// @brief Get the definition of a specific field by name.
      /// @param[in] name identifies the desired field instruction.
      /// @param[out] value is set to point to the field instruction if it is found.
      /// @returns true if the field instruction is found.  False if it is not defined in this segment.
      bool getInstruction(const std::string & name, FieldInstructionCPtr & value)const;

      /// @brief Get the definition of a specific field by index.
      /// @param[in] index identifies the desired field.
      /// @param[out] value is set to point to the field instruction if it is found.
      /// @returns true if the field instruction is found.  False if it is not defined in this segment.
      bool getInstruction(size_t index, FieldInstructionCPtr & value)const;

      /// @brief Access the instruction with the assumption that it exists.
      /// @param[in] index identifies the desired field.
      /// @returns a reference to the field instruction.
      FieldInstructionCPtr SegmentBody::getInstruction(size_t index)const;

      /// @brief Access the FieldInstructs for the length field (if any)
      /// @param value receives the length field instruction
      /// @returns true if one exists for this SegmentBody
      bool getLengthInstruction(FieldInstructionCPtr & value)const;

      void setMandatoryLength(bool mandatory)
      {
        mandatoryLength_ = mandatory;
      }
    protected:
      /// @brief the application data type for this set of fields
      std::string applicationType_;
      /// @brief the namespace for the application type name
      std::string applicationNamespace_;
      /// @brief the default dictionary to be used for this set of fields
      std::string dictionaryName_;
      /// @brief the maximum number of presence map bits needed to encode these fields
      size_t presenceMapBits_;
      /// @brief the number of presence map bits before any fields are added.
      size_t initialPresenceMapBits_;
      /// @brief the container type for instructions
      typedef std::vector<FieldInstructionPtr> InstructionVector;
      /// @brief the instructions
      InstructionVector instructions_;
      /// @brief true if this is being used as the body of a sequence
      bool allowLengthField_;
      /// @brief is the length field mandatory?
      bool mandatoryLength_;
      /// @brief the field instruction for sequence length if this is the body of a sequence
      FieldInstructionCPtr lengthInstruction_;
    };
  }
}
#endif // SEGMENTBODY_H
