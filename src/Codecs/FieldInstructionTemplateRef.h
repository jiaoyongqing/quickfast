// Copyright (c) 2009, Object Computing, Inc.
// All rights reserved.
// See the file license.txt for licensing information.
#ifdef _MSC_VER
# pragma once
#endif
#ifndef FIELDINSTRUCTIONTEMPLATEREF_H
#define FIELDINSTRUCTIONTEMPLATEREF_H
#include <Codecs/FieldInstruction.h>
namespace QuickFAST{
  namespace Codecs{
    /// @brief Implement static &lt;templateRef> field instruction.
    class QuickFAST_Export FieldInstructionStaticTemplateRef : public FieldInstruction
    {
    public:
      /// @brief construct with a name and a namespace
      /// @param name is the local name
      /// @param fieldNamespace is the namespace to qualify this name
      FieldInstructionStaticTemplateRef(
        const std::string & name,
        const std::string & fieldNamespace);

      /// @brief construct anonomous field instruction
      FieldInstructionStaticTemplateRef();

      /// @brief a typical virtual destructor.
      virtual ~FieldInstructionStaticTemplateRef();

      virtual void finalize(TemplateRegistry & templateRegistry);
      virtual size_t fieldCount(const SegmentBody & parent)const;

      virtual bool decodeNop(
        Codecs::DataSource & source,
        Codecs::PresenceMap & pmap,
        Codecs::Decoder & decoder,
        Messages::ValueMessageBuilder & fieldSet) const;

      virtual void encodeNop(
        Codecs::DataDestination & destination,
        Codecs::PresenceMap & pmap,
        Codecs::Encoder & encoder,
        const Messages::MessageAccessor & fieldSet) const;

      virtual size_t presenceMapBitsRequired() const;

    private:
      void interpretValue(const std::string & value);

    private:
      std::string templateName_;
      std::string templateNamespace_;
      size_t presenceMapBitsRequired_;
    };

    /// @brief Implement dynamic &lt;templateRef> field instruction.
    class QuickFAST_Export FieldInstructionDynamicTemplateRef : public FieldInstruction
    {
    public:
      /// @brief construct anonomous field instruction
      FieldInstructionDynamicTemplateRef();

      /// @brief a typical virtual destructor.
      virtual ~FieldInstructionDynamicTemplateRef();

      virtual size_t fieldCount(const SegmentBody & parent)const;

      virtual bool decodeNop(
        Codecs::DataSource & source,
        Codecs::PresenceMap & pmap,
        Codecs::Decoder & decoder,
        Messages::ValueMessageBuilder & fieldSet) const;

      virtual void encodeNop(
        Codecs::DataDestination & destination,
        Codecs::PresenceMap & pmap,
        Codecs::Encoder & encoder,
        const Messages::MessageAccessor & fieldSet) const;


    private:
      void interpretValue(const std::string & value);

    private:
    };

  }
}
#endif // FIELDINSTRUCTIONTEMPLATEREF_H
